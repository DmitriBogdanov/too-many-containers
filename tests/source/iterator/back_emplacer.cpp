// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <algorithm> // ranges::equal
#include <concepts>  // ...
#include <iterator>  // back_insert_iterator<>
#include <vector>    // vector<>

#include <tmc/iterator/back_emplacer.hpp>
#include <tmc/utility/tuple.hpp>

TEST_CASE("Compile-time requirements") {
    using container = std::vector<int>;

    using std_iterator = std::back_insert_iterator <container>;
    using tmc_iterator = tmc::back_emplace_iterator<container>;

    container c;

    std_iterator std_iter(c);
    tmc_iterator tmc_iter(c);

    // Emplace / insert iterators are constructible from l-value references
    static_assert(std::constructible_from<std_iterator, container&>);
    static_assert(std::constructible_from<tmc_iterator, container&>);

    static_assert(not std::constructible_from<std_iterator, container&&>);
    static_assert(not std::constructible_from<tmc_iterator, container&&>);

    static_assert(not std::constructible_from<std_iterator, const container&>);
    static_assert(not std::constructible_from<tmc_iterator, const container&>);

    // Emplace / insert iterators are not default constructible
    static_assert(not std::default_initializable<std_iterator>);
    static_assert(not std::default_initializable<tmc_iterator>);

    // Emplace / insert iterators can be copied
    static_assert(std::copyable<std_iterator>);
    static_assert(std::copyable<tmc_iterator>);

    static_assert(std::movable<std_iterator>);
    static_assert(std::movable<tmc_iterator>);

    // Values can be emplaced / inserted with `operator=`
    static_assert(std::is_assignable_v<decltype(*std_iter), int>);
    static_assert(std::is_assignable_v<decltype(*tmc_iter), int>);

    // Factory method returns corresponding iterator types
    static_assert(std::same_as<std_iterator, decltype(std::back_inserter(c))>);
    static_assert(std::same_as<tmc_iterator, decltype(tmc::back_emplacer(c))>);
}

TEST_CASE("Single-argument emplacement") {
    using container = std::vector<int>;
    
    container c;
    
    auto out = tmc::back_emplacer(c);
    
    *out = 0;
    *out = 1;
    *out = 2;
    *out = 3;
    
    // Content should be correct after emplacement
    CHECK(std::ranges::equal(c, container{ 0, 1, 2, 3 }));
}

namespace {

    struct multi_argument_constructible {
        int    x;
        float  y;
        double z;
        
        constexpr multi_argument_constructible(int x, float y, double z) : x(x), y(y), z(z) {}
    };
    
} // namespace

TEST_CASE("Multi-argument emplacement") {
    using container = std::vector<multi_argument_constructible>;
    
    container c;
    
    auto out = tmc::back_emplacer(c);
    
    *out = tmc::make_emplace_args(1, 2.f, 3.0);
    *out = tmc::make_emplace_args(4, 5.f, 6.0);
    
    // Content should be correct after emplacement
    const auto checked_range = c;
    const auto correct_range = container{ multi_argument_constructible{ 1, 2.f, 3.0 }, multi_argument_constructible{ 4, 5.f, 6.0 } };
    
    const auto equality = [](auto&& lhs, auto&& rhs) {
        return tmc::make_tuple(lhs.x, lhs.y, lhs.z) == tmc::make_tuple(rhs.x, rhs.y, rhs.z);
    };
    
    CHECK(std::ranges::equal(checked_range, correct_range, equality));
}
