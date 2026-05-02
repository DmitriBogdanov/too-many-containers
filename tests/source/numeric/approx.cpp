// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/numeric/approx.hpp>

TEST_CASE("Tolerance & value type deduction") {
    // `approx` should deduce its tolerance & value type from the floating-point argument
    constexpr auto approx_from_f32 = tmc::approx{ float {} };
    constexpr auto approx_from_f64 = tmc::approx{ double{} };

    static_assert(std::same_as<decltype(approx_from_f32)::value_type,  float>);
    static_assert(std::same_as<decltype(approx_from_f64)::value_type, double>);

    // constexpr auto approx_from_i32 = tmc::approx{ int{} }; // won't compile, can't deduce

    // Explicit `double` tolerance, should deduce result in a `double` value type
    constexpr auto approx_f64_tol_from_i32 = tmc::approx<1e-6>{ std::int32_t{} };
    constexpr auto approx_f64_tol_from_f32 = tmc::approx<1e-6>{        float{} };
    constexpr auto approx_f64_tol_from_f64 = tmc::approx<1e-6>{       double{} };

    static_assert(std::same_as<decltype(approx_f64_tol_from_i32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_f64_tol_from_f32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_f64_tol_from_f64)::value_type, double>);

    constexpr auto approx_f32_tol_from_i32 = tmc::approx<1e-6f>{ std::int32_t{} };
    constexpr auto approx_f32_tol_from_f32 = tmc::approx<1e-6f>{        float{} };
    constexpr auto approx_f32_tol_from_f64 = tmc::approx<1e-6f>{       double{} };

    static_assert(std::same_as<decltype(approx_f32_tol_from_i32)::value_type, float>);
    static_assert(std::same_as<decltype(approx_f32_tol_from_f32)::value_type, float>);
    static_assert(std::same_as<decltype(approx_f32_tol_from_f64)::value_type, float>);
}

TEST_CASE("Comparator behaviour") {
    static_assert(tmc::approx{ 0.0 } == 0);
    static_assert(0 == tmc::approx{ 0.0 });

    static_assert(tmc::approx{ 0.f } == 0);
    static_assert(0 == tmc::approx{ 0.f });

    static_assert(tmc::approx{ 1 + 1e-20 } == 1);
    static_assert(1 == tmc::approx{ 1 + 1e-20 });

    static_assert(tmc::approx{ 0.0 } != 2);
    static_assert(2 != tmc::approx{ 0.0 });

    static_assert(tmc::approx{ 0.0 } <= 2);
    static_assert(2 >= tmc::approx{ 0.0 });

    static_assert(tmc::approx{ 1 + 1e-20 } <= 1);
    static_assert(1 >= tmc::approx{ 1 + 1e-20 });

    static_assert(not(tmc::approx{ 1 + 1e-20 } < 1));
    static_assert(not(1 > tmc::approx{ 1 + 1e-20 }));

    static_assert(tmc::approx{ 0.0 } != std::numeric_limits<double>::max      ());
    static_assert(tmc::approx{ 0.0 } != std::numeric_limits<double>::infinity ());
    static_assert(tmc::approx{ 0.0 } != std::numeric_limits<double>::quiet_NaN());
}
