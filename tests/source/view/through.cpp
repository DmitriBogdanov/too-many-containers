// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/view/through.hpp>

TEST_CASE("View behaviour") {
    const auto indices = std::array{ 0, 0, 1, 2, 4 };
    const auto values  = std::array{ 10, 20, 30, 40, 50};
    
    const auto view = indices | tmc::views::through(values);
    
    CHECK(view[0] == 10);
    CHECK(view[1] == 10);
    CHECK(view[2] == 20);
    CHECK(view[3] == 30);
    CHECK(view[4] == 50);
    
    using view_type = decltype(view);
    
    using checked_value_type = std::ranges::range_value_t<view_type>;
    using correct_value_type = int;
    
    static_assert(std::same_as<checked_value_type, correct_value_type>);
    
    static_assert(std::ranges::random_access_range<view_type>);
}
