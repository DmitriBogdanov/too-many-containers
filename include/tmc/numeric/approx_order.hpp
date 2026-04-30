// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <compare>  // std::partial_ordering
#include <concepts> // floating_point
#include <limits>   // std::numeric_limits<>

#include <tmc/macro/no_discard.hpp>
#include <tmc/numeric/absdiff.hpp>
#include <tmc/numeric/isfinite.hpp>

namespace tmc {
    
// Floating-point compare function that uses approximate comparison with `tolerance`,
// values with a difference below tolerance are considered to be equal.
//
// This behaviour preserves partial ordering.
//
template <std::floating_point T>
TMC_NO_DISCARD
constexpr std::partial_ordering approx_order(
    T lhs, T rhs, T tolerance = std::numeric_limits<T>::epsilon()
) noexcept {
    const auto eval_lhs_is_finite = [&] { return tmc::isfinite(lhs);                 };
    const auto eval_rhs_is_finite = [&] { return tmc::isfinite(rhs);                 };
    const auto eval_diff_is_small = [&] { return tmc::absdiff(lhs, rhs) < tolerance; };
    
    if (eval_lhs_is_finite() and eval_rhs_is_finite() and eval_diff_is_small())
        return std::partial_ordering::equivalent;
    
    return std::partial_order(lhs, rhs);
}

} // namespace tmc
