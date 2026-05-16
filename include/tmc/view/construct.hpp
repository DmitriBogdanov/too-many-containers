// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // views::transform

#include <tmc/projection/construct.hpp>

namespace tmc::views {

template <class T>
inline constexpr auto construct = std::views::transform(projections::construct<T>{});
    
} // namespace tmc::views
