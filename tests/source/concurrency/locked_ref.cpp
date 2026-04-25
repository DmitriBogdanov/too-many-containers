// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

// Content: `tmc::locked_ref<T>` tests

#include <common/framework.hpp>

#include <shared_mutex> // std::shared_mutex

#include <tmc/concurrency/locked_ref.hpp> // tmc::locked_ref<>


namespace {

struct some_structure {
    std::uint32_t member_0 = {};
    std::uint64_t member_1 = {};

    bool method() const { return true; }
};

bool is_even(std::size_t value) { return value % 2 == 0; }

} // namespace


TEST_CASE("Locked reference to primitive") {
    std::size_t count = {};
    std::mutex  mutex = {};

    // Locked reference should deduce types
    auto reference = tmc::locked_ref{ count, mutex };

    using expected_locked_ref_type = tmc::locked_ref<std::size_t, std::scoped_lock<std::mutex>>;

    static_assert(std::same_as<decltype(reference), expected_locked_ref_type>);

    // Operator & function semantics should be similar to a regular reference
    CHECK(count == 0);

    reference += 1;

    CHECK(count == 1);

    CHECK(reference + 5 == 6);

    CHECK(is_even(++reference));

    // Assignment should work on the underlying object like with a regular reference
    // (unlike, for example, `std::reference_wrapper<T>` which can be rebound)
    reference = 8;

    CHECK(count == 8);
}

TEST_CASE("Locked reference to class") {
    some_structure    object  = { .member_0 = 10, .member_1 = 20 };
    std::mutex        mutex_0 = {};
    std::shared_mutex mutex_1 = {};

    // Locked ref should deduce multiple mutexes as a scoped lock
    auto reference = tmc::locked_ref{ object, mutex_0, mutex_1 };

    using expected_locked_ref_type = tmc::locked_ref<some_structure, std::scoped_lock<std::mutex, std::shared_mutex>>;

    static_assert(std::same_as<decltype(reference), expected_locked_ref_type>);

    // When bound to a structure, we should be able to access members with `->` operator
    CHECK(reference->member_0 == 10);
    CHECK(reference->member_1 == 20);
    CHECK(reference->method());
}

TEST_CASE("Locked reference constraints") {
    using scoped_lock = std::scoped_lock<std::mutex>;
    using unique_lock = std::unique_lock<std::mutex>;

    using scoped_locked_ref = tmc::locked_ref<int, scoped_lock>;
    using unique_locked_ref = tmc::locked_ref<int, unique_lock>;

    // Some lock types allow default initialization and moving, e.g. unique lock:
    static_assert(not std::default_initializable<scoped_lock>);
    static_assert(std::default_initializable<unique_lock>);

    static_assert(not std::copyable<scoped_lock>);
    static_assert(not std::copyable<unique_lock>);

    static_assert(not std::movable<scoped_lock>);
    static_assert(std::movable<unique_lock>);

    // Locked references are always non-empty, they cannot be default
    // initialized (even if the underlying lock is default-initializable)
    static_assert(not std::default_initializable<scoped_locked_ref>);
    static_assert(not std::default_initializable<unique_locked_ref>);

    // Locked reference are immovable and cannot be rebound (like regular references)
    static_assert(not std::copyable<scoped_locked_ref>);
    static_assert(not std::movable<scoped_locked_ref>);

    static_assert(not std::copyable<unique_locked_ref>);
    static_assert(not std::movable<unique_locked_ref>);

    static_assert(not tmc::req::copy_assignable<scoped_locked_ref>);
    static_assert(not tmc::req::copy_assignable<unique_locked_ref>);

    static_assert(not tmc::req::move_assignable<scoped_locked_ref>);
    static_assert(not tmc::req::move_assignable<unique_locked_ref>);
}
