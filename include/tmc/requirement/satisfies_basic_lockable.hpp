// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

namespace tmc {

// Named requirement `BasicLockable`, see https://en.cppreference.com/cpp/named_req/BasicLockable
//
template <class L>
concept satisfies_basic_lockable = requires(L m) {
    { m.  lock() };
    { m.unlock() } /* noexcept */;

    // Note: While `unlock()` is required to not throw any exceptions, it is NOT required to actually
    //       be marked `noexcept`. Standard mutex implementations are really patchy on whether they
    //       apply `noexcept` to `unlock()`, so we have to relax the concept for the sake of compliance.
};


} // namespace tmc
