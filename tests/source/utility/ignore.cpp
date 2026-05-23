// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/utility/ignore.hpp>

namespace {

[[nodiscard]] constexpr bool nodiscard_function() noexcept { return true; }

} // namespace

TEST_CASE("Invocation ignore") {
    tmc::ignore(true);

    tmc::ignore(nodiscard_function()); // should not produce any warnings
}

TEST_CASE("Assignment ignore") {
    tmc::ignore = true;

    tmc::ignore = nodiscard_function(); // should not produce any warnings
}
