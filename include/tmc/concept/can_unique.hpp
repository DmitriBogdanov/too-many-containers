// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <iterator> // permutable<>, indirect_equivalence_relation<>, projected<>
#include <ranges>   // ranges::forward_range<>, ranges::iterator_t<>

#include <tmc/functional/equal.hpp>
#include <tmc/projection/identity.hpp>

namespace tmc {

// Satisfied when `R` is a valid input for `std::ranges::unique` algorithm
template <class R, class Comp = equal, class Proj = projections::identity>
concept can_unique = requires {
    requires std::ranges::forward_range<R>;
    requires std::permutable<std::ranges::iterator_t<R>>;
    requires std::indirect_equivalence_relation<Comp, std::projected<std::ranges::iterator_t<R>, Proj>>;
};

} // namespace tmc
