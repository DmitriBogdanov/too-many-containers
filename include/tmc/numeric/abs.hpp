// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/concept/is_arithmetic.hpp>
#include <tmc/macro/no_discard.hpp>

namespace tmc {

template <is_arithmetic T>
TMC_NO_DISCARD constexpr T abs(T value) noexcept {
    return value >= T(0) ? value : -value;
}

} // namespace tmc
