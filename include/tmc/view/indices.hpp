// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // ranges::input_range<>, ranges::distance(), views::iota, ...

namespace tmc::views {

inline constexpr auto indices = [] <std::ranges::input_range R> (R&& range) {
    const auto distance = std::ranges::distance(std::forward<R>(range));

    return std::views::iota(std::ranges::range_difference_t<R>(0), distance);
};

} // namespace tmc::views
