// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <algorithm> // ranges::max

#include <tmc/optional/try_execute.hpp>

TEST_CASE("Try execute `std::ranges::max` on an empty range") {
    using range_type = std::vector<int>;
    
    const auto max = tmc::try_execute(std::ranges::max, range_type{}).value_or(0);
    
    CHECK(max == 0);
    
    using checked_result_type = tmc::try_execute_result_t<decltype(std::ranges::max), range_type>;
    using correct_result_type = tmc::optional<int>;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}

TEST_CASE("Try execute `std::ranges::max` on a non-empty range") {
    using range_type = std::vector<int>;
    
    const auto max = tmc::try_execute(std::ranges::max, range_type{ 2, 7, 3 }).value_or(0);
    
    CHECK(max == 7);
    
    using checked_result_type = tmc::try_execute_result_t<decltype(std::ranges::max), range_type>;
    using correct_result_type = tmc::optional<int>;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}
