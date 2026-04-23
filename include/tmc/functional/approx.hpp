// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Floating-point wrapper for comparing with tolerance

#include <compare>  // std::partial_ordering
#include <concepts> // std::floating_point<>, std::same_as<>
#include <limits>   // std::numeric_limits<>

#include <tmc/utility/math.hpp> // tmc::math::isfinite(), tmc::math::distance()


namespace tmc {

// Floating-point comparison is a partial ordering
static_assert(std::same_as<decltype(1.0 <=> 2.0), std::partial_ordering>);
static_assert(std::same_as<decltype(1.f <=> 2.f), std::partial_ordering>);

// Comparator that compares values as approximate using `epsilon` tolerance
// (values with a difference below tolerance are considered to be equal).
//
// This behaviour preserves partial ordering.
// Template type parameter can be omitted since it's deducible from the tolerance.
//
template <auto epsilon>
    requires std::floating_point<decltype(epsilon)>
struct approx {
    using value_type = decltype(epsilon);

    constexpr static value_type tolerance = epsilon;

    value_type value{};

    // Non-explicit constructor enables heterogenous comparison with other types (they get converted for comparison)
    constexpr approx(value_type value) noexcept : value(value) {}

    // Approximate comparator
    [[nodiscard]] constexpr std::partial_ordering operator<=>(approx other) const noexcept {
        static_assert(std::three_way_comparable<value_type, std::partial_ordering>);

        const auto eval_lhs_is_finite = [&] { return math::isfinite(this->value); };
        const auto eval_rhs_is_finite = [&] { return math::isfinite(other.value); };
        const auto eval_diff_is_small = [&] { return math::distance(this->value, other.value) < approx::tolerance; };

        if (eval_lhs_is_finite() and eval_rhs_is_finite() and eval_diff_is_small())
            return std::partial_ordering::equivalent;

        return std::partial_order(this->value, other.value);
    }

    // Partial ordering does not synthesize equality unless we explicitly specify it
    [[nodiscard]] constexpr bool operator==(approx other) const noexcept { return std::is_eq(*this <=> other); };
};

// `approx{ value }` should only work for floating-point values using their corresponding epsilon as
// tolerance, we don't want `approx{ int{} }` to compile without manually specifying its interpretation
template <std::floating_point T>
approx(T) -> approx<std::numeric_limits<T>::epsilon()>;

} // namespace tmc
