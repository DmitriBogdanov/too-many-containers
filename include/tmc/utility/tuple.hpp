// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tuple> // tuple<>, make_tuple(), forward_as_tuple(), apply(), get()

namespace tmc {

// Note: API stub for future re-implementation. Using modern metaprogramming `std::tuple` 
//       can be implemented in a significantly more efficient manner (both in terms of 
//       compile time overhead and runtime overhead). The reason same optimization
//       cannot be applied to the standard tuple is ABI ossification, see
//       https://github.com/codeinred/tuplet and Boost.Beast internals for more details.

template <class... Args>
using tuple = std::tuple<Args...>;

using std::make_tuple;
using std::forward_as_tuple;
using std::apply;
using std::get;
    
} // namespace tmc
