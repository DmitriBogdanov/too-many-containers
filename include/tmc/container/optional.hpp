// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <optional> // optional<>

namespace tmc {

template <class T>
using optional = std::optional<T>;

using nullopt_t = std::nullopt_t;

inline constexpr nullopt_t nullopt = std::nullopt;

// Note: API left as customization point, we might want to support reference types,
//       ranges and `void` instantiation. C++26 delivers on everything except `void`.

} // namespace tmc
