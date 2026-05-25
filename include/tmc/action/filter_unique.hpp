// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <algorithm> // ranges::sort, ranges::unique
#include <ranges>    // ranges::range_adaptor_closure<>, ranges::iterator_t<>
#include <utility>   // forward()

#include <tmc/concept/can_sort.hpp>
#include <tmc/concept/can_unique.hpp>
#include <tmc/concept/has_erase_range.hpp>
#include <tmc/functional/equal.hpp>
#include <tmc/functional/less.hpp>
#include <tmc/projection/identity.hpp>

namespace tmc::actions {

struct filter_unique_t : std::ranges::range_adaptor_closure<filter_unique_t> {

    template <class R, class Comp = less, class Equal = equal, class Proj = projections::identity>
        requires has_erase_range<R> and can_sort<R, Comp, Proj> and can_unique<R, Equal, Proj>
    constexpr decltype(auto) operator()(R&& range, Comp&& comp = {}, Equal&& equal = {}, Proj&& proj = {}) const {
        std::ranges::sort(range, std::forward<Comp>(comp), proj);

        const auto [mid, end] = std::ranges::unique(range, std::forward<Equal>(equal), proj);

        range.erase(mid, end);

        return std::forward<R>(range);
    }

};

inline constexpr auto filter_unique = filter_unique_t{};

} // namespace tmc::actions
