// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // integral<>
#include <ranges>   // views::iota

namespace tmc::views {

inline constexpr auto counted = [] <std::integral T> (T size) {
    return std::views::iota(T(0), size);
};

} // namespace tmc::views
