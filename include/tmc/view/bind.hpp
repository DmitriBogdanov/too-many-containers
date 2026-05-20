// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // views::transform

#include <tmc/projection/bind.hpp>

namespace tmc::views {

template <auto function>
inline constexpr auto bind = std::views::transform(projections::bind<function>{});

} // namespace tmc::views
