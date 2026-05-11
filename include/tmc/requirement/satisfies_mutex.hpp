// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>

#include <tmc/requirement/satisfies_lockable.hpp>

namespace tmc {

// Named requirement `Mutex`, see https://en.cppreference.com/cpp/named_req/Mutex
//
template <class L>
concept satisfies_mutex = requires {
    requires satisfies_lockable<L>;

    requires std::default_initializable<L>;
    requires std::destructible         <L>;

    requires not std::copyable<L>;
    requires not std::movable <L>;
};

} // namespace tmc
