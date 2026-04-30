// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cmath>    // isfinite()
#include <concepts> // floating_point

#include <tmc/macro/no_discard.hpp>
#include <tmc/numeric/isinf.hpp>
#include <tmc/numeric/isnan.hpp>

namespace tmc {

template <std::floating_point T>
TMC_NO_DISCARD constexpr bool isfinite(T value) noexcept {
    if consteval {
        return not tmc::isnan(value) and not tmc::isinf(value);
    } else {
        return std::isfinite(value);
    }
}

} // namespace tmc
