// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Allocator-aware equivalent of `std::unique_ptr<T>`

#include <memory> // std::unique_ptr<>, std::construct_at(), std::destroy_at()

#include <tmc/concept/structure.hpp> // tmc::req::nothrow_copy_constructible<>
#include <tmc/memory/allocator.hpp>  // tmc::allocator<>
#include <tmc/utility/platform.hpp>  // TMC_NO_UNIQUE_ADDRESS


namespace tmc::detail {

template <class Alloc>
struct allocator_deleter {
    using allocator_type = Alloc;

    TMC_NO_UNIQUE_ADDRESS allocator_type alloc;

public:
    allocator_deleter(const allocator_type& alloc = {}) noexcept(req::nothrow_copy_constructible<allocator_type>)
        : alloc(alloc) {}

    void operator()(auto* ptr) {
        std::destroy_at(ptr); // invokes the destructor

        this->alloc.deallocate(ptr, 1);
    }
};

} // namespace tmc::detail


namespace tmc {

template <class T, class Alloc = tmc::allocator<T>>
using allocation_ptr = std::unique_ptr<T, detail::allocator_deleter<Alloc>>;

template <class T, class Alloc, class... Args>
[[nodiscard]] constexpr auto allocate_unique(const Alloc& alloc, Args&&... args) {
    // Following the convention of `std::allocate_shared<T>()`,
    // we should rebind allocator in case its type didn't match
    using rebound_allocator = typename std::allocator_traits<Alloc>::template rebind_alloc<T>;
    using allocator_deleter = detail::allocator_deleter<rebound_allocator>;

    auto deleter = allocator_deleter{ rebound_allocator{ alloc } };

    // Allocate memory & placement-new-construct into it, in case construction
    // threw an exception we should cleanup allocation & rethrow it down the stack
    auto* ptr = deleter.alloc.allocate(1);

    try {
        ptr = std::construct_at(ptr, std::forward<Args>(args)...);
    } catch (...) {
        deleter.alloc.deallocate(ptr, 1);
        throw;
    }

    return tmc::allocation_ptr<T, rebound_allocator>{ ptr, std::move(deleter) };
}

} // namespace tmc
