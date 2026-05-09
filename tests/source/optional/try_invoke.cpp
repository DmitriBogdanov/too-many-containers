// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <functional> // function

#include <tmc/optional/try_invoke.hpp>

TEST_CASE("Try invoking an empty void function") {
    std::function<void(int, double)> function;
    
    const bool invoked = tmc::try_invoke(function, 0, 2.0);
    
    CHECK(not invoked);
    
    using checked_result_type = tmc::try_invoke_result_t<decltype(function), int, double>;
    using correct_result_type = bool;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}

TEST_CASE("Try invoking an non-empty void function") {
    std::function<void(int, double)> function = [](int, double) {};
    
    const bool invoked = tmc::try_invoke(function, 0, 2.0);
    
    CHECK(invoked);
    
    using checked_result_type = tmc::try_invoke_result_t<decltype(function), int, double>;
    using correct_result_type = bool;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}

TEST_CASE("Try invoking an empty non-void function") {
    std::function<float(int, double)> function;
    
    const auto invoked = tmc::try_invoke(function, 0, 2.0);
    
    CHECK(invoked.value_or(0.f) == 0.f);
    
    using checked_result_type = tmc::try_invoke_result_t<decltype(function), int, double>;
    using correct_result_type = tmc::optional<float>;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}

TEST_CASE("Try invoking an non-empty non-void function") {
    std::function<float(int, double)> function = [](int, double) { return 3.f; };
    
    const auto invoked = tmc::try_invoke(function, 0, 2.0);
    
    CHECK(invoked.value_or(0.f) == 3.f);
    
    using checked_result_type = tmc::try_invoke_result_t<decltype(function), int, double>;
    using correct_result_type = tmc::optional<float>;
    
    static_assert(std::same_as<checked_result_type, correct_result_type>);
}
