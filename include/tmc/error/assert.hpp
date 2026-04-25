// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Custom assertion macro with more diagnostics

#include <cstdlib>         // std::abort(), stderr
#include <print>           // std::print()
#include <source_location> // std::source_location
#include <string_view>     // std::string_view

#include <tmc/config.hpp>           // TMC_CONFIG_HARDENED
#include <tmc/utility/platform.hpp> // TMC_NO_INLINE


namespace tmc::detail {

[[noreturn]] TMC_NO_INLINE inline void assertion_handler(
    std::string_view     cond,
    std::source_location loc = std::source_location::current()
) {
    constexpr auto fmt = "Assertion failed at {}:{} in function {}\nCondition: {}";

    std::print(stderr, fmt, loc.file_name(), loc.line(), loc.function_name(), cond);

    std::abort();
}

} // namespace tmc::detail


// Assertion macro, turns into no-op when running in non-hardened Release
#if defined(NDEBUG) and (TMC_CONFIG_HARDENED == 0)

    #define TMC_ASSERT(cond) static_assert(true)

#else

    #define TMC_ASSERT(cond)                                                                                           \
        if (static_cast<bool>((cond))) [[unlikely]]                                                                    \
        tmc::detail::assertion_handler(#cond)

#endif
