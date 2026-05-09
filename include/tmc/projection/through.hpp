// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

#include <tmc/concept/has_at.hpp>
#include <tmc/functional/singular_closure.hpp>
#include <tmc/macro/no_discard.hpp>

namespace tmc::projections {

// Projects value "though" a container:
//
//    value -> container.at(value)
//
// This is often useful for running algorithms on ranges that index into another range, e.g.:
//
//    > const auto edge_indices = std::array{ 2, 3, 5 };
//    > const auto edge_weights = std::array{ 0., 0., 2., 7., 0., 5. }
//    >
//    > const auto max_edge = std::ranges::max(edge_indices, tmc::less_by{ tmc::projections::through{ edge_weights } });
//
template <class Container>
struct through : singular_closure<Container> {

    template <class Arg>
        requires has_at<Container, Arg>
    TMC_NO_DISCARD constexpr decltype(auto) operator()(Arg&& arg) const {
        return this->value.at(std::forward<Arg>(arg));
    }

};

template <class Container>
through(Container&&) -> through<Container>;

// Note: It could be argued that `operator[]` is also a good fit for mapping, and we should pick
//       `operator[]` / `at()` based on availability, however `at()` provides a safer default due
//       to bound checking, while also avoiding the issue of some classes (like maps) having
//       potentially mutating `operator[]`. We don't want projection to suddenly insert into
//       the referenced container (which can invalidate the projected range causing a disaster),
//       but we do want it to allow mutable references to elements which `at` does.

} // namespace tmc::projections
