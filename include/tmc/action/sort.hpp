// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <algorithm> // ranges::sort, sortable<>
#include <ranges>    // ranges::random_access_range<>, ranges::iterator_t<>
#include <utility>   // forward()

#include <tmc/functional/less.hpp>
#include <tmc/concept/can_sort.hpp>

namespace tmc::actions {

struct sort_t : std::ranges::range_adaptor_closure<sort_t> {

    template <std::ranges::random_access_range R, class Comp = less, class Proj = std::identity>
        requires can_sort<R, Comp, Proj>
    constexpr decltype(auto) operator()(R&& range, Comp&& comp = {}, Proj&& proj = {}) const {
        std::ranges::sort(range, std::forward<Comp>(comp), std::forward<Proj>(proj));

        return std::forward<R>(range);
    }

};

inline constexpr auto sort = sort_t{};

} // namespace tmc::actions
