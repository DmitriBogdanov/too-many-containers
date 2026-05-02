// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/concept/has_is_transparent.hpp>
#include <tmc/functional/equal.hpp>
#include <tmc/functional/greater.hpp>
#include <tmc/functional/greater_equal.hpp>
#include <tmc/functional/hash.hpp>
#include <tmc/functional/less.hpp>
#include <tmc/functional/less_equal.hpp>
#include <tmc/functional/not_equal.hpp>

TEST_CASE("Transparent hash and comparators") {
    static_assert(tmc::has_is_transparent<tmc::equal        >);
    static_assert(tmc::has_is_transparent<tmc::not_equal    >);
    static_assert(tmc::has_is_transparent<tmc::greater      >);
    static_assert(tmc::has_is_transparent<tmc::greater_equal>);
    static_assert(tmc::has_is_transparent<tmc::less         >);
    static_assert(tmc::has_is_transparent<tmc::less_equal   >);

    static_assert(tmc::has_is_transparent<tmc::hash>);
}
