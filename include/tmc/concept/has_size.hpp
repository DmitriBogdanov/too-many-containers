// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>
#include <cstddef>  // size_t

namespace tmc {

template <class R>
concept has_size = requires(R range) {
    { range.size() } -> std::convertible_to<std::size_t>;
};
    
} // namespace tmc
