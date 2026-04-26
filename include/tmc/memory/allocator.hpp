// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Default TMC allocator & allocator traits API

#include <memory> // std::allocator<>

#include <tmc/concept/requirements.hpp> // tmc::allocator<>, tmc::allocator_for<>


namespace tmc {

template <class T>
using allocator = std::allocator<T>;

} // namespace tmc


namespace tmc::memory {

// Below is a 1-to-1 reflection of `std::allocator_traits<>`, but in a form of
// free types and functions, which means we get type deduction that makes most
// operations significantly less verbose, e.g. instead of doing this:
//
//    > using rebound_allocator = std::allocator_traits<Alloc>::template rebind_alloc<T>;
//    >
//    > auto* ptr = std::allocator_traits<Alloc>::allocate(alloc, n);
//
// We can do this for the same effect:
//
//    > using rebound_allocator = detail::rebind_alloc<Alloc, T>;
//    >
//    > auto* ptr = detail::allocate(alloc, n);
//
// This API also enforces allocator constraints at an appropriate level
// (when performing actions that require `value_type` to be complete).

// Member types

template <class Alloc>
using allocator_type = std::allocator_traits<Alloc>::allocator_type;

template <class Alloc>
using value_type = std::allocator_traits<Alloc>::value_type;

template <class Alloc>
using pointer = std::allocator_traits<Alloc>::pointer;

template <class Alloc>
using const_pointer = std::allocator_traits<Alloc>::const_pointer;

template <class Alloc>
using void_pointer = std::allocator_traits<Alloc>::void_pointer;

template <class Alloc>
using const_void_pointer = std::allocator_traits<Alloc>::const_void_pointer;

template <class Alloc>
using difference_type = std::allocator_traits<Alloc>::difference_type;

template <class Alloc>
using size_type = std::allocator_traits<Alloc>::size_type;

template <class Alloc>
using propagate_on_container_copy_assignment = std::allocator_traits<Alloc>::propagate_on_container_copy_assignment;

template <class Alloc>
using propagate_on_container_move_assignment = std::allocator_traits<Alloc>::propagate_on_container_move_assignment;

template <class Alloc>
using propagate_on_container_swap = std::allocator_traits<Alloc>::propagate_on_container_swap;

template <class Alloc>
using is_always_equal = std::allocator_traits<Alloc>::is_always_equal;

// Member alias templates

template <class Alloc, class T>
using rebind_alloc = std::allocator_traits<Alloc>::template rebind_alloc<T>;

template <class Alloc, class T>
using rebind_traits = std::allocator_traits<Alloc>::template rebind_traits<T>;

// Member functions

template <req::allocator Alloc>
[[nodiscard]] constexpr pointer<Alloc> allocate(Alloc& alloc, size_type<Alloc> n) {
    return std::allocator_traits<Alloc>::allocate(alloc, n);
}

template <req::allocator Alloc>
[[nodiscard]] constexpr pointer<Alloc> allocate(Alloc& alloc, size_type<Alloc> n, const_void_pointer<Alloc> hint) {
    return std::allocator_traits<Alloc>::allocate(alloc, n, hint);
}

template <req::allocator Alloc>
constexpr void deallocate(Alloc& alloc, pointer<Alloc> p, size_type<Alloc> n) {
    return std::allocator_traits<Alloc>::deallocate(alloc, p, n);
}

template <class Alloc, class T, class... Args>
    requires req::allocator_for<Alloc, T>
constexpr void construct(Alloc& alloc, T* p, Args&&... args) {
    return std::allocator_traits<Alloc>::construct(alloc, p, std::forward<Args>(args)...);
}

template <class Alloc, class T>
    requires req::allocator_for<Alloc, T>
constexpr void destroy(Alloc& alloc, T* p) {
    return std::allocator_traits<Alloc>::destroy(alloc, p);
}

template <class Alloc>
[[nodiscard]] constexpr size_type<Alloc> max_size(const Alloc& alloc) {
    return std::allocator_traits<Alloc>::max_size(alloc);
}

} // namespace tmc::memory
