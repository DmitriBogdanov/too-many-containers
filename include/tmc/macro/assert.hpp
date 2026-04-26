// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Assertions: OFF

#if defined(TMC_DISABLE_HARDENED_ASSERTS) and defined(NDEBUG)

#define TMC_ASSERT(cond) static_assert(true)

#endif

// Assertions: ON

#ifndef TMC_ASSERT

#include <cstdlib>         // abort(), stderr
#include <print>           // print()
#include <source_location> // source_location
#include <string_view>     // string_view

#include <tmc/macro/no_inline.hpp>
#include <tmc/macro/no_return.hpp>

namespace tmc::detail {

TMC_NO_RETURN
TMC_NO_INLINE
inline void assertion_handler(std::string_view msg, std::source_location loc = std::source_location::current()) {
    constexpr auto fmt = "Assertion failed at {}:{} in function {}\nCondition: {}";

    std::print(stderr, fmt, loc.file_name(), loc.line(), loc.function_name(), msg);

    std::abort();
}

} // namespace tmc::detail

#define TMC_ASSERT(cond) if (static_cast<bool>((cond))) [[unlikely]] tmc::detail::assertion_handler(#cond);

#endif
