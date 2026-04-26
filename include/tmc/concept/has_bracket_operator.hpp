// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/concept/is_non_void.hpp>

namespace tmc {

template <class R, class K>
concept has_bracket_operator = requires(R range, K key) {
    { range[key] } -> is_non_void;
};
    
} // namespace tmc
