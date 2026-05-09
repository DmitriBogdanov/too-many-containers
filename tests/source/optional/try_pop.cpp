// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <deque>
#include <queue>
#include <stack>

#include <tmc/optional/try_pop.hpp>

TEST_CASE("Try pop from stack") {
    std::stack<int> values;
    
    values.push(1);
    values.push(2);
    values.push(3);
    
    CHECK(tmc::try_pop(values).value_or(0) == 3); // LIFO order
    CHECK(tmc::try_pop(values).value_or(0) == 2); //
    CHECK(tmc::try_pop(values).value_or(0) == 1); //
    CHECK(tmc::try_pop(values).value_or(0) == 0); //
    
    using checked_result_type = tmc::try_pop_result_t<decltype(values)>;
    using correct_result_type = tmc::optional<int>;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}

TEST_CASE("Try pop from queue") {
    std::queue<int> values;
    
    values.push(1);
    values.push(2);
    values.push(3);
    
    CHECK(tmc::try_pop(values).value_or(0) == 1); // FIFO order
    CHECK(tmc::try_pop(values).value_or(0) == 2); //
    CHECK(tmc::try_pop(values).value_or(0) == 3); //
    CHECK(tmc::try_pop(values).value_or(0) == 0); //
    
    using checked_result_type = tmc::try_pop_result_t<decltype(values)>;
    using correct_result_type = tmc::optional<int>;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}

template <class C>
concept can_try_pop = requires (C c) {
    tmc::try_pop(c);
};

TEST_CASE("Compile-time ambiguity protection") {
    static_assert(    can_try_pop<std::stack<int>>);
    static_assert(    can_try_pop<std::queue<int>>);
    static_assert(not can_try_pop<std::deque<int>>);
}
