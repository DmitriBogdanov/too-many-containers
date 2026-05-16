// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // views::transform

#include <tmc/projection/through.hpp>

namespace tmc::views {

inline constexpr auto through = [] <class Container> (Container&& c) {
    return std::views::transform(projections::through<Container>{ std::forward<Container>(c) });
};

} // namespace tmc::views
