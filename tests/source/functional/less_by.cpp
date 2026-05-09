// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <algorithm>   // ranges::max
#include <array>       // array<>
#include <string_view> // string_view
#include <utility>     // pair<>

#include <tmc/functional/less_by.hpp>
#include <tmc/projection/through.hpp>
#include <tmc/projection/value.hpp>

TEST_CASE("Compare by statefull projection") {
    constexpr auto edge_indices = std::array{ 2, 3, 5 };
    constexpr auto edge_weights = std::array{ 0., 1., 2., 7., 4., 5. };

    constexpr auto max_edge = std::ranges::max(edge_indices, tmc::less_by{ tmc::projections::through{ edge_weights } });
    
    static_assert(max_edge == 3);
}

TEST_CASE("Compare by stateless projection") {
    using namespace std::string_view_literals;

    constexpr auto pairs = std::array{
        std::pair{ "key_0"sv, 0. },
        std::pair{ "key_1"sv, 1. },
        std::pair{ "key_2"sv, 2. },
        std::pair{ "key_3"sv, 7. },
        std::pair{ "key_4"sv, 4. }
    };

    constexpr auto max_pair = std::ranges::max(pairs, tmc::less_by<tmc::projections::value>{});

    static_assert(max_pair.first == "key_3"sv);
}

namespace {
    
    struct vec3{ double x, y, z; };
    
};

TEST_CASE("Compare by projection with unusual invocation") {
    constexpr auto vectors = std::array{
        vec3{ 7., 0., 2. },
        vec3{ 4., 1., 5. },
        vec3{ 1., 2., 4. },
        vec3{ 3., 7., 8. },
        vec3{ 0., 4., 9. }
    };

    constexpr auto max_vector = std::ranges::max(vectors, tmc::less_by{ &vec3::y });

    static_assert(max_vector.x == 3.);
    static_assert(max_vector.y == 7.);
    static_assert(max_vector.z == 8.);
    
    // Note: Pointer-to-member projection requires `std::invoke()` for
    //       proper invocation, a naive implementation might miss it.
}
