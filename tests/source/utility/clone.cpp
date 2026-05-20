// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <concepts> // copyable<>, same_as<>

#include <common/framework.hpp>

#include <tmc/utility/clone.hpp>
#include <tmc/concept/is_explicitly_copyable.hpp>

namespace {

struct explicitly_copyable {
    bool moved = false;

    explicitly_copyable() = default;

    explicit explicitly_copyable(const explicitly_copyable&) = default;

    explicitly_copyable(explicitly_copyable&&) noexcept : moved(true) {}
};

static_assert(not std::              copyable<explicitly_copyable>);
static_assert(    tmc::is_explicitly_copyable<explicitly_copyable>);

} // namespace

TEST_CASE("Compatibility of clone with move semantics") {
    auto value = explicitly_copyable{};

    const auto copy_result = tmc::clone(std::as_const(value));
    const auto move_result = tmc::clone(std::    move(value));

    CHECK(copy_result.moved == false);
    CHECK(move_result.moved == true );
    
    static_assert(std::same_as<decltype(copy_result), const explicitly_copyable>);
    static_assert(std::same_as<decltype(move_result), const explicitly_copyable>);
}
