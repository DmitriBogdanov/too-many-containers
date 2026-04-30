// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cmath>    // isnan()
#include <concepts> // floating_point

#include <tmc/macro/no_discard.hpp>

namespace tmc {

template <std::floating_point T>
TMC_NO_DISCARD constexpr bool isnan(T value) noexcept {
    if consteval {
        return value != value;
    } else {
        return std::isnan(value);
    }
}

} // namespace tmc
