// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/view/cast.hpp>

TEST_CASE("View behaviour") {
    const auto range = std::array{ 0.1, 1.1, 2.1, 3.1 };
    
    const auto view = range | tmc::views::cast<int>;
    
    CHECK(view[0] == 0);
    CHECK(view[1] == 1);
    CHECK(view[2] == 2);
    
    using view_type = decltype(view);
    
    using checked_value_type = std::ranges::range_value_t<view_type>;
    using correct_value_type = int;
    
    static_assert(std::same_as<checked_value_type, correct_value_type>);
    
    static_assert(std::ranges::random_access_range<view_type>);
}
