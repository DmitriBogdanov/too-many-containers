// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // same_as<>

#include <tmc/requirement/satisfies_basic_lockable.hpp>

namespace tmc {

// Named requirement `Lockable`, see https://en.cppreference.com/cpp/named_req/Lockable
//
template <class L>
concept satisfies_lockable = requires(L m) {
    requires satisfies_basic_lockable<L>;

    { m.try_lock() } -> std::same_as<bool>;

    // Note 1: Since `try_lock()` is explicitly specified to return `true` / `false`, we require
    //         strict equivalence to `bool` return type rather than just checking convertibility

    // Note 2: While `try_lock()` is required to not throw any exceptions, it is NOT required to actually
    //         be marked `noexcept`. Standard mutex implementations are really patchy on whether they
    //         apply `noexcept` to `try_lock()`, so we have to relax the concept for the sake of compliance.
};


} // namespace tmc
