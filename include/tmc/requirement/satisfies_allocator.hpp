// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <memory> // allocator_traits<>

#include <tmc/concept/is_cv_unqualified.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>
#include <tmc/requirement/is_nothrow_copy_assignable.hpp>
#include <tmc/requirement/is_nothrow_copy_constructible.hpp>
#include <tmc/requirement/is_nothrow_move_assignable.hpp>
#include <tmc/requirement/is_nothrow_move_constructible.hpp>
#include <tmc/requirement/satisfies_object.hpp>

namespace tmc::detail {

struct dummy_type {};

} // namespace tmc::detail

namespace tmc {

// Named requirement `Allocator`, see https://en.cppreference.com/cpp/named_req/Allocator
//
// Note that this requirement is more pedantic than the suggested exposition-only concept
// from C++26, here we actually verify `noexcept` guarantees and fancy pointer operations.
//
// Important: This concept should NOT be applied at the top level when building containers
//            as it requires `T` to be complete (there is no way to verify all requirements
//            for an incomplete value type), instead it should be used to constrain functions
//            that do the actual object creation / destruction / allocation / deallocation.
//
template <class A, class T = std::allocator_traits<A>::value_type>
concept satisfies_allocator = requires(
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
    requires satisfies_object<T>;
    requires is_cv_unqualified<T>;

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
    requires is_nothrow_copy_constructible<A>;
    requires is_nothrow_copy_assignable<A>;

    requires is_nothrow_constructible<A, const decltype(b)&>;

    requires is_nothrow_move_constructible<A>;
    requires is_nothrow_move_assignable<A>;

    requires is_nothrow_constructible<A, decltype(b)&&>;
};

} // namespace tmc
