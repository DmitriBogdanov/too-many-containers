// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <iterator> // sortable<>
#include <ranges>   // ranges::random_access_range<>, ranges::iterator_t<>

#include <tmc/functional/less.hpp>
#include <tmc/projection/identity.hpp>

namespace tmc {

// Satisfied when `R` is a valid input for `std::ranges::sort` algorithm
template <class R, class Comp = less, class Proj = projections::identity>
concept can_sort = requires {
    requires std::ranges::random_access_range<R>;
    requires std::sortable<std::ranges::iterator_t<R>, Comp, Proj>;
};

} // namespace tmc
