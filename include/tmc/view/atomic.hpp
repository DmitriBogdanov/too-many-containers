// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // views::transform

#include <tmc/projection/atomic.hpp>

namespace tmc::views {

inline constexpr auto atomic = std::views::transform(projections::atomic{});

} // namespace tmc::views
