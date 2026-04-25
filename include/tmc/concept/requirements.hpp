// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Named requirements (https://en.cppreference.com/cpp/named_req) translated into concepts

#include <concepts> // std::same_as<>
#include <memory>   // std::allocator_traits<>

#include <tmc/concept/primitive.hpp> // tmc::req::cv_unqualified<>
#include <tmc/concept/structure.hpp> // tmc::req::nothrow_constructible<>, ...


namespace tmc::req::detail {

struct dummy_type {};

} // namespace tmc::req::detail


namespace tmc::req {

// Note: For better clarity, when implementing requirements we will match
//       the order & naming used by cppreference, in some cases this
//       may produce inconsistency with the rest of the codebase.



// `Allocator` named requirement, see https://en.cppreference.com/cpp/named_req/Allocator
//
// Note that this requirement is more pedantic than the suggested exposition-only concept
// from C++26, here we actually verify `noexcept` guarantees and fancy pointer operations.
//
template <class A, class T>
concept allocator_for = requires(
    A                                                                   a,
    T                                                                   t,
    std::allocator_traits<A>::template rebind_alloc<detail::dummy_type> b,
    std::allocator_traits<A>::pointer                                   p,
    std::allocator_traits<A>::const_pointer                             cp,
    std::allocator_traits<A>::void_pointer                              vp,
    std::allocator_traits<A>::const_void_pointer                        cvp,
    std::allocator_traits<A>::size_type                                 n
) {
    // Allocated type requirements
    requires req::cv_unqualified<T>;

    // Member type requirements
    requires std::same_as<T, typename A::value_type>;

    // Pointer expressions requirements
    { *p } -> std::same_as<T&>;
    { *cp } -> std::same_as<const T&>;

    // Allocator expressions requirements
    { a.allocate(n) } -> std::same_as<decltype(p)>;

    a.deallocate(p, n);

    static_cast<decltype(p)>(vp);
    static_cast<decltype(cp)>(cvp);

    // Instance relationship requirements
    { a == a } -> std::same_as<bool>;
    { a != a } -> std::same_as<bool>;

    // Construction requirements
    requires req::nothrow_copy_constructible<A>;
    requires req::nothrow_copy_assignable<A>;

    requires req::nothrow_constructible<A, const decltype(b)&>;

    requires req::nothrow_move_constructible<A>;
    requires req::nothrow_move_assignable<A>;

    requires req::nothrow_constructible<A, decltype(b)&&>;
};

} // namespace tmc::req
