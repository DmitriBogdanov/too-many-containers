// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cmath>    // isinf()
#include <concepts> // floating_point
#include <limits>   // numeric_limits<>

#include <tmc/macro/no_discard.hpp>

namespace tmc {

template <std::floating_point T>
TMC_NO_DISCARD constexpr bool isinf(T value) noexcept {
    if consteval {
        const bool is_positive_inf = (value == +std::numeric_limits<T>::infinity());
        const bool is_negative_inf = (value == -std::numeric_limits<T>::infinity());

        return is_positive_inf or is_negative_inf;
    } else {
        return std::isinf(value);
    }
}

} // namespace tmc
