// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

// Content: Approximate float comparator tests

#include <common/framework.hpp>

#include <tmc/functional/approx.hpp> // tmc::approx<>


TEST_CASE("Compile-time math") {
    static_assert(tmc::math::isfinite(0.0));
    static_assert(tmc::math::isfinite(1e-19));
    
    static_assert(tmc::math::isfinite(std::numeric_limits<float>::lowest()));
    static_assert(tmc::math::isfinite(std::numeric_limits<float>::epsilon()));
    static_assert(tmc::math::isfinite(std::numeric_limits<float>::min()));
    static_assert(tmc::math::isfinite(std::numeric_limits<float>::max()));
    
    static_assert(not tmc::math::isfinite(std::numeric_limits<float>::infinity()));
    static_assert(not tmc::math::isfinite(std::numeric_limits<float>::quiet_NaN()));
    static_assert(not tmc::math::isfinite(std::numeric_limits<float>::signaling_NaN()));
    
    static_assert(tmc::math::distance(0.0, 1.0) == 1.0);
    static_assert(tmc::math::distance(1.0, 0.0) == 1.0);
}

TEST_CASE("Approx float comparator type") {
    // By default approx. is always interpreted `double`
    constexpr auto approx_from_i32 = tmc::approx{ std::int32_t{} };
    constexpr auto approx_from_f32 = tmc::approx{ float{} };
    constexpr auto approx_from_f64 = tmc::approx{ double{} };
    
    static_assert(std::same_as<decltype(approx_from_i32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_from_f32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_from_f64)::value_type, double>);
    
    // If we specify `double` tolerance, it should deduce `double`
    constexpr auto approx_f64_tol_from_i32 = tmc::approx<1e-6>{ std::int32_t{} };
    constexpr auto approx_f64_tol_from_f32 = tmc::approx<1e-6>{ float{} };
    constexpr auto approx_f64_tol_from_f64 = tmc::approx<1e-6>{ double{} };
    
    static_assert(std::same_as<decltype(approx_f64_tol_from_i32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_f64_tol_from_f32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_f64_tol_from_f64)::value_type, double>);
    
    constexpr auto approx_f32_tol_from_i32 = tmc::approx<1e-6>{ std::int32_t{} };
    constexpr auto approx_f32_tol_from_f32 = tmc::approx<1e-6>{ float{} };
    constexpr auto approx_f32_tol_from_f64 = tmc::approx<1e-6>{ double{} };
    
    static_assert(std::same_as<decltype(approx_f32_tol_from_i32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_f32_tol_from_f32)::value_type, double>);
    static_assert(std::same_as<decltype(approx_f32_tol_from_f64)::value_type, double>);
}

TEST_CASE("Approx float comparator behaviour") {
    static_assert(tmc::approx{ 0.0 } == 0);
    static_assert(0 == tmc::approx{ 0.0 });
    
    static_assert(tmc::approx{ 1 + 1e-20 } == 1);
    static_assert(1 == tmc::approx{ 1 + 1e-20 });
    
    static_assert(tmc::approx{ 0.0 } != 2);
    static_assert(2 != tmc::approx{ 0.0 });
    
    static_assert(tmc::approx{ 0.0 } <= 2);
    static_assert(2 >= tmc::approx{ 0.0 });
    
    static_assert(tmc::approx{ 1 + 1e-20 } <= 1);
    static_assert(1 >= tmc::approx{ 1 + 1e-20 });
    
    static_assert(not (tmc::approx{ 1 + 1e-20 } < 1));
    static_assert(not (1 > tmc::approx{ 1 + 1e-20 }));
    
    static_assert(tmc::approx{ 0.0 } != std::numeric_limits<double>::max());
    static_assert(tmc::approx{ 0.0 } != std::numeric_limits<double>::infinity());
    static_assert(tmc::approx{ 0.0 } != std::numeric_limits<double>::quiet_NaN());
}
