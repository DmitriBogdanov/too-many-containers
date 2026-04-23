// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Closure base types

#include <tmc/utility/tuple.hpp> // tmc::tuple


namespace tmc {

// Base class for single-value closures. To avoid dangling references on r-value
// capture, r-values should be captured by value & moved into the closure, e.g.:
//
//    singular_closure{ <  const reference> } -> singular_closure<const T&>
//    singular_closure{ <l-value reference> } -> singular_closure<      T&>
//    singular_closure{ <r-value reference> } -> singular_closure<      T >
//    singular_closure{ <            value> } -> singular_closure<      T >
//
// This is achievable by providing CTAD guides for perfect forwarding.
//
template <class T>
struct singular_closure {
    using value_type = T;

    value_type value;
};

template <class T>
singular_closure(T&&) -> singular_closure<T>;

// Base class for multi-value closures. Same principles as before apply on per-element basis.
//
template <class... Args>
struct variadic_closure {
    using value_type = tmc::tuple<Args...>;

    value_type value;

    variadic_closure(Args&&... args) : value(std::forward<Args>(args)...) {}
};

template <class... Args>
variadic_closure(Args&&...) -> variadic_closure<Args...>;

} // namespace tmc
