// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

// Content:

#include <common/framework.hpp>

#include <utility> // std::as_const()

#include <tmc/concept/structure.hpp>  // tmc::req::transparent<>
#include <tmc/functional/closure.hpp> // tmc::singular_closure<>
#include <tmc/functional/compare.hpp> // tmc::less, tmc::greater, tmc::equal, ...
#include <tmc/functional/hash.hpp>    // tmc::hash


TEST_CASE("Transparent hash and comparators") {

    static_assert(tmc::req::transparent<tmc::equal>);
    static_assert(tmc::req::transparent<tmc::not_equal>);
    static_assert(tmc::req::transparent<tmc::greater>);
    static_assert(tmc::req::transparent<tmc::greater_equal>);
    static_assert(tmc::req::transparent<tmc::less>);
    static_assert(tmc::req::transparent<tmc::less_equal>);

    static_assert(tmc::req::transparent<tmc::hash>);
}

TEST_CASE("Singular closure capture") {
    int value = 0;

    // Closures should capture l-values by reference and r-values by value
    const auto c_closure = tmc::singular_closure{std::as_const(value)};
    const auto l_closure = tmc::singular_closure{value};
    const auto r_closure = tmc::singular_closure{std::move(value)};
    const auto v_closure = tmc::singular_closure{1};

    static_assert(std::same_as<decltype(c_closure)::value_type, const int&>);
    static_assert(std::same_as<decltype(l_closure)::value_type, int&>);
    static_assert(std::same_as<decltype(r_closure)::value_type, int>);
    static_assert(std::same_as<decltype(v_closure)::value_type, int>);
}

TEST_CASE("Variadic closure capture") {
    std::uint16_t a = 0;
    std::uint32_t b = 1;
    std::uint64_t c = 2;

    // Closures should capture l-values by reference and r-values by value
    const auto closure = tmc::variadic_closure{a, std::as_const(b), std::move(c), 1};

    using expected_value_type = tmc::tuple<std::uint16_t&, const std::uint32_t&, std::uint64_t, int>;

    static_assert(std::same_as<decltype(closure)::value_type, expected_value_type>);
}
