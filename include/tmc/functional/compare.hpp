// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Transparent comparator functors

#include <functional> // std::equal_to<>, std::greater<>, std::less<>, ...

#include <tmc/functional/closure.hpp> // tmc::singular_closure<>


namespace tmc {

// Transparent comparators

using less          = std::less<>;
using less_equal    = std::less_equal<>;
using greater       = std::greater<>;
using greater_equal = std::greater_equal<>;
using equal         = std::equal_to<>;
using not_equal     = std::not_equal_to<>;

// Closures for comparison against a bound value

// 1) From `less`
template <class T>
struct less_than : singular_closure<T> {
    template <class Arg>
    constexpr auto operator()(const Arg& arg) {
        return tmc::less{}(arg, this->value);
    }
};

template <class T>
less_than(T&&) -> less_than<T>;

// 2) From `less_equal`
template <class T>
struct less_equal_than : singular_closure<T> {
    template <class Arg>
    constexpr auto operator()(const Arg& arg) {
        return tmc::less_equal{}(arg, this->value);
    }
};

template <class T>
less_equal_than(T&&) -> less_equal_than<T>;

// 3) From `greater`
template <class T>
struct greater_than : singular_closure<T> {
    template <class Arg>
    constexpr auto operator()(const Arg& arg) {
        return tmc::greater{}(arg, this->value);
    }
};

template <class T>
greater_than(T&&) -> greater_than<T>;

// 4) From `greater_equal`
template <class T>
struct greater_equal_than : singular_closure<T> {
    template <class Arg>
    constexpr auto operator()(const Arg& arg) {
        return tmc::greater_equal{}(arg, this->value);
    }
};

template <class T>
greater_equal_than(T&&) -> greater_equal_than<T>;

// 5) From `equal`
template <class T>
struct equal_to : singular_closure<T> {
    template <class Arg>
    constexpr auto operator()(const Arg& arg) {
        return tmc::equal{}(arg, this->value);
    }
};

template <class T>
equal_to(T&&) -> equal_to<T>;

// 6) From `not_equal`
template <class T>
struct not_equal_to : singular_closure<T> {
    template <class Arg>
    constexpr auto operator()(const Arg& arg) {
        return tmc::not_equal{}(arg, this->value);
    }
};

template <class T>
not_equal_to(T&&) -> not_equal_to<T>;


} // namespace tmc
