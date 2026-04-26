// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>        // constructible_from
#include <source_location> // source_location

namespace tmc {

// Problem:
//
//    We want to write variadic functions that capture `std::source_location`, yet there is no way to
//    have a default `std::source_location` parameter after the argument pack, e.g. this will not work:
//
//    > template <class Args...>
//    > void function(std::format_string<Args...> fmt, Args&&... args, std::source_location loc = ...);
//
// Solution:
//
//    For functions that have a fixed non-variadic parameter (like `std::format_string<Args...>`)
//    this parameter can be "exploited" by adding a thin wrapper around it that
//    automatically captures `std::source_location` in its constructor.
//
template <class T>
struct source_location_capture {
    T                    val;
    std::source_location loc;

    template <class Arg>
        requires std::constructible_from<T, Arg>
    consteval source_location_capture(
        Arg&& arg, std::source_location loc = std::source_location::current()
    ) noexcept
        : val(std::forward<Arg>(arg)), loc(loc) {}
};

} // namespace tmc
