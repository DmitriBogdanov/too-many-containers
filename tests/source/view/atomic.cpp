// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/view/atomic.hpp>

TEST_CASE("View behaviour (const range)") {
    const auto range = std::array{ 0, 1, 2 };
    
    const auto view = range | tmc::views::atomic;
    
    CHECK(view[0] == 0);
    CHECK(view[1] == 1);
    CHECK(view[2] == 2);
    
    using view_type = decltype(view);
    
    using checked_value_type = std::ranges::range_value_t<view_type>;
    using correct_value_type = int;
    
    static_assert(std::same_as<checked_value_type, correct_value_type>);
    
    using checked_reference_type = std::ranges::range_reference_t<view_type>;
    using correct_reference_type = const int&;
    
    static_assert(std::same_as<checked_reference_type, correct_reference_type>);
    
    static_assert(std::ranges::random_access_range<view_type>);
}

TEST_CASE("View behaviour (mutable range)") {
    auto range = std::array{ 0, 1, 2 };
    
    const auto view = range | tmc::views::atomic;
    
    CHECK(view[0] == 0);
    CHECK(view[1] == 1);
    CHECK(view[2] == 2);
    
    using view_type = decltype(view);
    
    using checked_value_type = std::ranges::range_value_t<view_type>;
    using correct_value_type = std::atomic_ref<int>;
    
    static_assert(std::same_as<checked_value_type, correct_value_type>);
    
    using checked_reference_type = std::ranges::range_reference_t<view_type>;
    using correct_reference_type = std::atomic_ref<int>;
    
    static_assert(std::same_as<checked_reference_type, correct_reference_type>);
    
    static_assert(std::ranges::random_access_range<view_type>);
}
