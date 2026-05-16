// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // views::transform

#include <tmc/projection/cast.hpp>

namespace tmc::views {

template <class T>
inline constexpr auto cast = std::views::transform(projections::cast<T>{});
    
} // namespace tmc::views
