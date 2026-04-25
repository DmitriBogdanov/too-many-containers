// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Utility for capturing <source_location> in error-handling functions

#include <format>          // std::format_string<>
#include <source_location> // std::source_location


namespace tmc {

// Problem:
//
//    We want to write variadic functions that capture 'std::source_location', yet there is no way to
//    have a default 'std::source_location' parameter after the argument pack, e.g. this will not work:
//
//    > template <class Args...>
//    > void func(std::format_string<Args...> fmt, Args&&... args, std::source_location loc = ...);
//
// Solution:
//
//    For functions that have a fixed non-variadic parameter (like 'std::format_string<Args...>') this
//    parameter can be "exploited" by adding a wrapper that automatically captures 'std::source_location'.
//
template <class... Args>
struct format_string_with_location {
    std::format_string<Args...> fmt;
    std::source_location        loc;

    template <class T>
    consteval format_string_with_location(
        const T&             str,
        std::source_location loc = std::source_location::current()
    ) noexcept
        : fmt(str), loc(loc) {}

    consteval format_string_with_location(
        std::format_string<Args...> fmt,
        std::source_location        loc = std::source_location::current()
    ) noexcept
        : fmt(fmt), loc(loc) {}
};

} // namespace tmc
