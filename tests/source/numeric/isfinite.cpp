// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/numeric/isfinite.hpp>

TEST_CASE("Constexpr evaluation") {
    static_assert(tmc::isfinite(0.000));
    static_assert(tmc::isfinite(1e-19));

    static_assert(tmc::isfinite(std::numeric_limits<float>::lowest ()));
    static_assert(tmc::isfinite(std::numeric_limits<float>::epsilon()));
    static_assert(tmc::isfinite(std::numeric_limits<float>::min    ()));
    static_assert(tmc::isfinite(std::numeric_limits<float>::max    ()));

    static_assert(not tmc::isfinite(std::numeric_limits<float>::infinity     ()));
    static_assert(not tmc::isfinite(std::numeric_limits<float>::quiet_NaN    ()));
    static_assert(not tmc::isfinite(std::numeric_limits<float>::signaling_NaN()));
}
