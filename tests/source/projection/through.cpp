// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <array>         // array<>
#include <string>        // string
#include <unordered_map> // unordered_map<>

#include <tmc/projection/through.hpp>

TEST_CASE("Projection though an array") {
    constexpr auto weights = std::array{ 0., 1., 2., 7., 4. };

    static_assert(tmc::projections::through{ weights }(0) == 0.);
    static_assert(tmc::projections::through{ weights }(1) == 1.);
    static_assert(tmc::projections::through{ weights }(2) == 2.);
    static_assert(tmc::projections::through{ weights }(3) == 7.);
    static_assert(tmc::projections::through{ weights }(4) == 4.);

    CHECK_THROWS(tmc::projections::through{ weights }(5)); // out of bounds access should throw
}

TEST_CASE("Projection though a map") {
    const auto weights = std::unordered_map<std::string, double>{
        { "key_0", 0. },
        { "key_1", 1. },
        { "key_2", 2. },
        { "key_3", 7. },
        { "key_4", 4. }
    };

    CHECK(tmc::projections::through{ weights }("key_0") == 0.);
    CHECK(tmc::projections::through{ weights }("key_1") == 1.);
    CHECK(tmc::projections::through{ weights }("key_2") == 2.);
    CHECK(tmc::projections::through{ weights }("key_3") == 7.);
    CHECK(tmc::projections::through{ weights }("key_4") == 4.);

    CHECK_THROWS(tmc::projections::through{ weights }("key_5")); // out of bounds access should throw
}

TEST_CASE("Mutable access though a projection") {
    auto weights = std::array{ 0., 1., 2., 7., 4. };
    
    tmc::projections::through{ weights }(0) = 5.;
    tmc::projections::through{ weights }(2) = 8.;
    
    CHECK(weights.at(0) == 5.);
    CHECK(weights.at(1) == 1.);
    CHECK(weights.at(2) == 8.);
    CHECK(weights.at(3) == 7.);
    CHECK(weights.at(4) == 4.);
}
