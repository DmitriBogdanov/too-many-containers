// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Tuple type used by the library

#include <tuple> // std::tuple<>


namespace tmc {

template <class... Args>
using tuple = std::tuple<Args...>;

// Note: Ideally, we should re-implement tuple using fold expressions and modern metaprogramming,
//       this can significantly cut down on compile times for large tuples and even affects
//       performance for trivial types (`std::tuple` cannot be made trivially copyable or
//       rewritten due to ABI ossification, see https://github.com/codeinred/tuplet and
//       Boost.Beast internal tuple implementation.

using std::make_tuple;
using std::forward_as_tuple;
using std::apply;
using std::get;

} // namespace tmc
