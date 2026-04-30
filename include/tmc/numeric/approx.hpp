// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <compare>  // std::partial_ordering
#include <concepts> // floating_point
#include <limits>   // std::numeric_limits<>

#include <tmc/numeric/approx_order.hpp>

namespace tmc {

// Floating-point value wrapper that compares floats as approximate using `tolerance`,
// values with a difference below tolerance are considered to be equal.
//
// Floating-point type is deduced from the tolerance value.
//
template <auto compare_tolerance>
    requires std::floating_point<decltype(compare_tolerance)>
struct approx {
    using value_type = decltype(compare_tolerance);

    constexpr static value_type tolerance = compare_tolerance;

    value_type value = {};

public:
    // Non-explicit constructor enables heterogenous comparison with other
    // arithmetic types (they get implicitly converted before comparison), cases
    // where such conversion is narrowing should be caught by compiler warnings
    constexpr approx(value_type value) noexcept : value(value) {}

    // Approximate comparator
    TMC_NO_DISCARD
    constexpr std::partial_ordering operator<=>(approx other) const noexcept {
        return approx_order(this->value, other.value, tolerance);
    }

    // Partial ordering does not synthesize equality unless we explicitly specify it
    TMC_NO_DISCARD
    constexpr bool operator==(approx other) const noexcept { return std::is_eq(*this <=> other); };
};

// `approx{ value }` should only work for floating-point values using their corresponding epsilon as
// tolerance, we don't want `approx{ int{} }` to compile without manually specifying its interpretation
template <std::floating_point T>
approx(T) -> approx<std::numeric_limits<T>::epsilon()>;

} // namespace tmc
