// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>
#include <ranges>   // ranges::iterator_t<>
#include <utility>  // pair<>

namespace tmc {

template <class R, class K>
concept has_equal_range = requires(R range, K key) {
    { range.equal_range(key) } -> std::convertible_to<std::pair<
        std::ranges::iterator_t<R>,
        std::ranges::iterator_t<R>
    >>;
};

} // namespace tmc
