// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <mutex>
#include <shared_mutex>

#include <tmc/concurrency/spin_mutex.hpp>
#include <tmc/requirement/satisfies_mutex.hpp>

TEST_CASE("Compile-time requirements") {
    static_assert(tmc::satisfies_mutex<std::       mutex>);
    static_assert(tmc::satisfies_mutex<std::shared_mutex>);
    static_assert(tmc::satisfies_mutex<tmc::  spin_mutex>);
}
