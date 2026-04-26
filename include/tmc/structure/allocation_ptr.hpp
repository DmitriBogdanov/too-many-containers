// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Allocator-aware equivalent of `std::unique_ptr<T>`

#include <memory> // std::unique_ptr<>

#include <tmc/concept/requirements.hpp>    // tmc::req::allocator_for<>
#include <tmc/memory/allocator.hpp>        // tmc::allocator<>, tmc::memory::construct(), tmc::memory::destroy(), ...
#include <tmc/utility/platform.hpp>        // TMC_NO_UNIQUE_ADDRESS


namespace tmc::detail {

template <class Alloc>
struct allocation_deleter {
    using allocator_type = Alloc;

    TMC_NO_UNIQUE_ADDRESS allocator_type alloc;

public:
    allocation_deleter(const allocator_type& alloc) noexcept : alloc(alloc) {}
    // conforming allocators guarantee `noexcept` copy

    void operator()(auto* ptr)
        requires req::allocator_for<Alloc, std::remove_pointer_t<decltype(ptr)>>
    {
        memory::destroy(this->alloc, ptr);
        memory::deallocate(this->alloc, ptr, 1);
    }
};

} // namespace tmc::detail


namespace tmc {

// `std::unique_ptr<T>` that allocates & destroys its object using an allocator.
//
// Important: `tmc::allocation_ptr<T>` does NOT support array types (e.g. `int[]`) as they are impossible
//            to support though a general allocator model (not without effectively turning the type into 
//            a dynamic array that also stores size), the reason `std::unique_ptr<>` can "get away" with
//            it is due to the black magic of global `new[]` and `delete[]` which store allocation size
//            implicitly using implementation-defined control block. And even with this implicit magic
//            `unique_ptr<T[]>` uses a separate specialization of default deleter to invoke `delete[]`
//            instead of the usual `delete`. Here we make a choice of being pedantic and refusing
//            arrays outright (use `tmc::dynamic_array<T, Alloc>` to get array pointers instead).
//
template <req::non_array T, class Alloc = tmc::allocator<T>>
using allocation_ptr = std::unique_ptr<T, detail::allocation_deleter<Alloc>>;

// Unique equivalent of `std::allocate_shared()`.
//
// Following the convention of `std::allocate_shared<T>()`,
// we rebind allocator in case its type doesn't match the `T`.
//
template <req::non_array T, class Alloc, class... Args> requires req::allocator_for<Alloc, T>
[[nodiscard]] constexpr auto allocate_unique(const Alloc& alloc, Args&&... args) {
    using rebound_allocator = memory::rebind_alloc<Alloc, T>;
    using allocator_deleter = detail::allocation_deleter<rebound_allocator>;

    auto deleter = allocator_deleter{ rebound_allocator{ alloc } };

    // Allocate memory & placement-new-construct into it, in case construction
    // threw an exception we should cleanup allocation & rethrow it down the stack
    auto* ptr = memory::allocate(deleter.alloc, 1);

    try {
        memory::construct(deleter.alloc, ptr, std::forward<Args>(args)...);
    } catch (...) {
        memory::deallocate(deleter.alloc, ptr, 1);

        throw;
    }

    return tmc::allocation_ptr<T, rebound_allocator>{ ptr, std::move(deleter) };
}

} // namespace tmc
