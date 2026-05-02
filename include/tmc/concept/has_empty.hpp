// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>

namespace tmc {

template <class R>
concept has_empty = requires(R range) {
    { range.empty() } -> std::convertible_to<bool>;
};
    
} // namespace tmc
