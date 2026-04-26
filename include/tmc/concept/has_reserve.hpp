// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef> // size_t

namespace tmc {

template <class R, class S = std::size_t>
concept has_reserve = requires(R range, S capacity) {
    range.reserve(capacity);
};
    
} // namespace tmc
