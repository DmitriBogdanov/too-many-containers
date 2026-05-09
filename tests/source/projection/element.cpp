// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tuple> // tuple<>, get()

#include <tmc/projection/element.hpp>

namespace {
    
    template <class T> concept can_std_get = requires (T value) { std::get<0>(value); };
    template <class T> concept can_adl_get = requires (T value) {      get<0>(value); };
    
} // namespace

TEST_CASE("Project elements of `std::tuple`") {
    using tuple_type = std::tuple<int, float, double>;
    
    static_assert(can_std_get<tuple_type>);
    static_assert(can_adl_get<tuple_type>);
    
    constexpr auto tuple = tuple_type{ 100, 2.f, 3.0 };
    
    static_assert(tmc::projections::element<0>{}(tuple) == 100);
    static_assert(tmc::projections::element<1>{}(tuple) == 2.f);
    static_assert(tmc::projections::element<2>{}(tuple) == 3.0);
    
    using checked_result_type_0 = decltype(tmc::projections::element<0>{}(tuple));
    using correct_result_type_0 = const int&;
    
    static_assert(std::same_as<checked_result_type_0, correct_result_type_0>);
    
    using checked_result_type_1 = decltype(tmc::projections::element<1>{}(tuple));
    using correct_result_type_1 = const float&;
    
    static_assert(std::same_as<checked_result_type_1, correct_result_type_1>);
    
    using checked_result_type_2 = decltype(tmc::projections::element<2>{}(tuple));
    using correct_result_type_2 = const double&;
    
    static_assert(std::same_as<checked_result_type_2, correct_result_type_2>);
}

namespace {
    
    struct vec3 {
        double x, y, z;
        
        template <std::size_t> friend constexpr double get(const vec3&) noexcept;
    };
    
    template <> constexpr double get<0>(const vec3& vec) noexcept { return vec.x; }
    template <> constexpr double get<1>(const vec3& vec) noexcept { return vec.y; }
    template <> constexpr double get<2>(const vec3& vec) noexcept { return vec.z; }
    
} // namespace

TEST_CASE("Project elements of custom tuple-like class") {
    using tuple_type = vec3;
    
    static_assert(not can_std_get<tuple_type>);
    static_assert(    can_adl_get<tuple_type>);
    
    constexpr auto tuple = tuple_type{ 1.0, 2.0, 3.0 };
    
    static_assert(tmc::projections::element<0>{}(tuple) == 1.0);
    static_assert(tmc::projections::element<1>{}(tuple) == 2.0);
    static_assert(tmc::projections::element<2>{}(tuple) == 3.0);
}
