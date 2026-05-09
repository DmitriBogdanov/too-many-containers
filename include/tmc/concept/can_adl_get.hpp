// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef> // size_t

#include <tmc/concept/is_non_void.hpp>

namespace tmc {

template <class T, std::size_t index = 0>
concept can_adl_get = requires (T value) {
    { get<index>(value) } -> is_non_void;
};
    
} // namespace tmc
