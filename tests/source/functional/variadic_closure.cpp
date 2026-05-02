// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <cstdint> // uint16_t, uint32_t, uint64_t
#include <utility> // as_const(), move()

#include <tmc/functional/variadic_closure.hpp>

TEST_CASE("Capture type correctness") {
    std::uint16_t a = 0;
    std::uint32_t b = 1;
    std::uint64_t c = 2;

    // Closures should capture l-values by reference and r-values by value
    const auto closure = tmc::variadic_closure{ a, std::as_const(b), std::move(c), 1 };

    using checked_value_type = decltype(closure)::value_type;
    using correct_value_type = tmc::tuple<std::uint16_t&, const std::uint32_t&, std::uint64_t, int>;

    static_assert(std::same_as<checked_value_type, correct_value_type>);
}
