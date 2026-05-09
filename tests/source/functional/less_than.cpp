// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <algorithm> // ranges::max
#include <array>     // array<>

#include <tmc/functional/less_than.hpp>

TEST_CASE("Compare to bound value") {
    constexpr auto weights = std::array{ 0., 1., 2., 7., 4., 5. };

    constexpr auto count = std::ranges::count_if(weights, tmc::less_than{ 3. });

    static_assert(count == 3);
}
