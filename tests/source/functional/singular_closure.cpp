// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <utility> // as_const(), move()

#include <tmc/functional/singular_closure.hpp>

TEST_CASE("Capture type correctness") {
    int value = 0;

    // Closures should capture l-values by reference and r-values by value
    const auto c_closure = tmc::singular_closure{ std::as_const(value) };
    const auto l_closure = tmc::singular_closure{               value  };
    const auto r_closure = tmc::singular_closure{     std::move(value) };
    const auto v_closure = tmc::singular_closure{                    1 };

    static_assert(std::same_as<decltype(c_closure)::value_type, const int&>);
    static_assert(std::same_as<decltype(l_closure)::value_type,       int&>);
    static_assert(std::same_as<decltype(r_closure)::value_type,       int >);
    static_assert(std::same_as<decltype(v_closure)::value_type,       int >);
}
