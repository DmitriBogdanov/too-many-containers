// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Allocator-aware equivalent of `std::unique_ptr<T>`

#include <memory> // std::unique_ptr<>

#include <tmc/concept/requirements.hpp>    // tmc::req::allocator_for<>
#include <tmc/detail/allocator_traits.hpp> // tmc::detail::destroy(), tmc::detail::construct(), ...
#include <tmc/memory/allocator.hpp>        // tmc::allocator<>
#include <tmc/utility/platform.hpp>        // TMC_NO_UNIQUE_ADDRESS


namespace tmc::detail {

template <class Alloc>
struct allocation_deleter {
    using allocator_type = Alloc;

    TMC_NO_UNIQUE_ADDRESS allocator_type alloc;

public:
    allocation_deleter(const allocator_type& alloc) noexcept : alloc(alloc) {}
    // conforming allocators guarantee `noexcept` copy
    
    void operator()(auto* ptr) {
        detail::destroy(this->alloc, ptr);
        detail::deallocate(this->alloc, ptr, 1);
    }
};

} // namespace tmc::detail


namespace tmc {

template <class T, req::allocator_for<T> Alloc = tmc::allocator<T>>
using allocation_ptr = std::unique_ptr<T, detail::allocation_deleter<Alloc>>;

template <class T, req::allocator_for<T> Alloc, class... Args>
[[nodiscard]] constexpr auto allocate_unique(const Alloc& alloc, Args&&... args) {
    // Following the convention of `std::allocate_shared<T>()`,
    // we should rebind allocator in case its type didn't match
    using rebound_allocator = detail::rebind_alloc<Alloc, T>;
    using allocator_deleter = detail::allocation_deleter<rebound_allocator>;

    auto deleter = allocator_deleter{ rebound_allocator{ alloc } };

    // Allocate memory & placement-new-construct into it, in case construction
    // threw an exception we should cleanup allocation & rethrow it down the stack
    auto* ptr = detail::allocate(deleter.alloc, 1);

    try {
        detail::construct(deleter.alloc, ptr, std::forward<Args>(args)...);
    } catch (...) {
        detail::deallocate(deleter.alloc, ptr, 1);

        throw;
    }

    return tmc::allocation_ptr<T, rebound_allocator>{ ptr, std::move(deleter) };
}

} // namespace tmc
