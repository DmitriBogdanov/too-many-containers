// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <mutex>        // mutex
#include <shared_mutex> // shared_mutex

#include <tmc/concurrency/locked_ref.hpp>
#include <tmc/requirement/is_copy_assignable.hpp>
#include <tmc/requirement/is_move_assignable.hpp>

TEST_CASE("Compile-time requirements") {
    using scoped_lock = std::scoped_lock<std::mutex>;
    using unique_lock = std::unique_lock<std::mutex>;

    using scoped_locked_ref = tmc::locked_ref<int, scoped_lock>;
    using unique_locked_ref = tmc::locked_ref<int, unique_lock>;

    // Some lock types allow default initialization and moving, e.g. unique lock:
    static_assert(not std::default_initializable<scoped_lock>);
    static_assert(    std::default_initializable<unique_lock>);

    static_assert(not std::copyable<scoped_lock>);
    static_assert(not std::copyable<unique_lock>);

    static_assert(not std::movable<scoped_lock>);
    static_assert(    std::movable<unique_lock>);

    // Locked references are always non-empty, they cannot be default
    // initialized (even if the underlying lock is default-initializable)
    static_assert(not std::default_initializable<scoped_locked_ref>);
    static_assert(not std::default_initializable<unique_locked_ref>);

    // Locked reference are immovable and cannot be rebound (like regular references)
    static_assert(not std::copyable<scoped_locked_ref>);
    static_assert(not std::movable <scoped_locked_ref>);

    static_assert(not std::copyable<unique_locked_ref>);
    static_assert(not std::movable <unique_locked_ref>);

    static_assert(not tmc::is_copy_assignable<scoped_locked_ref>);
    static_assert(not tmc::is_copy_assignable<unique_locked_ref>);

    static_assert(not tmc::is_move_assignable<scoped_locked_ref>);
    static_assert(not tmc::is_move_assignable<unique_locked_ref>);
}

TEST_CASE("Primitive type reference") {
    std::size_t count = {};
    std::mutex  mutex = {};
    
    const auto is_even = [] (std::size_t x) { return x % 2 == 0; };

    // `locked_ref` should provide CTAD with a scoped lock by default
    auto reference = tmc::locked_ref{ count, mutex };
    
    using checked_type = decltype(reference);
    using correct_type = tmc::locked_ref<std::size_t, std::scoped_lock<std::mutex>>;

    static_assert(std::same_as<checked_type, correct_type>);

    // Operator & function semantics should be similar to a regular reference
    CHECK(count == 0);

    reference += 1;

    CHECK(count == 1);

    CHECK(reference + 5 == 6);

    CHECK(is_even(++reference));

    // Assignment should work on the underlying object like with a regular reference
    // (unlike, for example, `std::reference_wrapper<T>` which can be rebound by assignment)
    reference = 8;

    CHECK(count == 8);
}

namespace {

struct some_structure {
    std::uint32_t member_0 = {};
    std::uint64_t member_1 = {};

    bool method() const { return true; }
};

} // namespace

TEST_CASE("Class reference") {
    some_structure    object  = { .member_0 = 10, .member_1 = 20 };
    std::mutex        mutex_0 = {};
    std::shared_mutex mutex_1 = {};

    // `locked_ref` should provide CTAD with a scoped lock by default
    auto reference = tmc::locked_ref{ object, mutex_0, mutex_1 };
    
    using checked_type = decltype(reference);
    using correct_type = tmc::locked_ref<some_structure, std::scoped_lock<std::mutex, std::shared_mutex>>;
    
    static_assert(std::same_as<checked_type, correct_type>);

    // When bound to a structure, we should be able to access members with `->` operator
    CHECK(reference->member_0 == 10);
    CHECK(reference->member_1 == 20);
    CHECK(reference->method()      );
}
