// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/view/indices.hpp>

TEST_CASE("Range category preservation") {
    constexpr auto range = std::array{ 10, 20, 30, 40 };
    
    constexpr auto indices = tmc::views::indices(range);
    
    using view_type = decltype(indices);
    
    static_assert(std::ranges::random_access_range<view_type>);
    static_assert(std::ranges::        sized_range<view_type>);
    
    static_assert(std::ranges::size(indices) == std::ranges::size(range));
    
    static_assert(indices[0] == 0);
    static_assert(indices[1] == 1);
    static_assert(indices[2] == 2);
    static_assert(indices[3] == 3);
}
