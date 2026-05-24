// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <algorithm> // ranges::equal
#include <concepts>  // same_as<>
#include <vector>    // vector<>

#include <tmc/action/sort.hpp>
#include <tmc/functional/greater.hpp>
#include <tmc/utility/clone.hpp>

TEST_CASE("Type forwarding") {
    auto range = std::vector{ 5, 4, 2, 3, 1, 0 };

    using checked_type_0 = decltype(tmc::actions::sort(range));
    using checked_type_1 = decltype(range | tmc::actions::sort);
    using checked_type_2 = decltype(tmc::actions::sort(tmc::clone(range)));
    using checked_type_3 = decltype(tmc::clone(range) | tmc::actions::sort);

    using correct_type_0 = std::vector<int>&;
    using correct_type_1 = std::vector<int>&;
    using correct_type_2 = std::vector<int>&&;
    using correct_type_3 = std::vector<int>&&;

    static_assert(std::same_as<checked_type_0, correct_type_0>);
    static_assert(std::same_as<checked_type_1, correct_type_1>);
    static_assert(std::same_as<checked_type_2, correct_type_2>);
    static_assert(std::same_as<checked_type_3, correct_type_3>);
}

TEST_CASE("Piping semantics") {
    auto range = std::vector{ 5, 4, 2, 3, 1, 0 };

    auto sorted_range_1 = tmc::actions::sort(range);  // option 1: regular invocation
    auto sorted_range_2 = range | tmc::actions::sort; // option 2: piped   invocation

    CHECK(std::ranges::equal(sorted_range_1, std::vector{ 0, 1, 2, 3, 4, 5 }));
    CHECK(std::ranges::equal(sorted_range_2, std::vector{ 0, 1, 2, 3, 4, 5 }));

    using checked_type_0 = decltype(sorted_range_1);
    using checked_type_1 = decltype(sorted_range_2);

    using correct_type_0 = std::vector<int>; // non-reference `auto`
    using correct_type_1 = std::vector<int>; // results in a copy

    static_assert(std::same_as<checked_type_0, correct_type_0>);
    static_assert(std::same_as<checked_type_1, correct_type_1>);

    // Optional parameters can only be specified when using direct invocation syntax
    auto reverse_sorted_range = tmc::actions::sort(range, tmc::greater{});

    CHECK(std::ranges::equal(reverse_sorted_range, std::vector{ 5, 4, 3, 2, 1, 0 }));
}
