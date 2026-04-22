// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Compile-time math and additional functions

#include <cmath>    // std::isnan(), std::isinf(), std::isfinite()
#include <concepts> // std::floating_point<>


namespace tmc::math {

template <std::floating_point T>
[[nodiscard]] constexpr bool isnan(T value) noexcept {
    if consteval {
        return value != value;
    } else {
        return std::isnan(value);
    }
}

template <std::floating_point T>
[[nodiscard]] constexpr bool isinf(T value) noexcept {
    if consteval {
        const bool is_positive_inf = (value == +std::numeric_limits<T>::infinity());
        const bool is_negative_inf = (value == -std::numeric_limits<T>::infinity());

        return is_positive_inf or is_negative_inf;
    } else {
        return std::isinf(value);
    }
}

template <std::floating_point T>
[[nodiscard]] constexpr bool isfinite(T value) noexcept {
    if consteval {
        return not math::isnan(value) and not math::isinf(value);
    } else {
        return std::isfinite(value);
    }
}

template <std::floating_point T>
[[nodiscard]] constexpr T abs(T value) noexcept {
    return (value >= T(0)) ? value : -value;
}

template <std::floating_point T>
[[nodiscard]] constexpr T distance(T lhs, T rhs) noexcept {
    return math::abs(lhs - rhs);
}

} // namespace tmc::math
