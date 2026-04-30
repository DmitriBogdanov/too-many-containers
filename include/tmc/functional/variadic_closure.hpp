// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

#include <tmc/requirement/is_nothrow_constructible.hpp>
#include <tmc/utility/tuple.hpp>

namespace tmc {

// Base class for multi-value closures. To avoid dangling references on r-value
// capture, r-values should be captured by value & moved into the closure, e.g.:
//
//    variadic_closure{ ... <  const reference> ... } -> variadic_closure< ... const T& ... >
//    variadic_closure{ ... <l-value reference> ... } -> variadic_closure< ...       T& ... >
//    variadic_closure{ ... <r-value reference> ... } -> variadic_closure< ...       T  ... >
//    variadic_closure{ ... <            value> ... } -> variadic_closure< ...       T  ... >
//
// This is achievable by providing CTAD guides for perfect forwarding.
// The principle applies on per-member basis.
//
template <class... Args>
struct variadic_closure {
    using value_type = tmc::tuple<Args...>;

    value_type value;

    constexpr variadic_closure(Args&&... args)
        noexcept(is_nothrow_constructible<value_type, Args...>)
    :
        value(std::forward<Args>(args)...) {}
};

template <class... Args>
variadic_closure(Args&&...) -> variadic_closure<Args...>;
    
} // namespace tmc
