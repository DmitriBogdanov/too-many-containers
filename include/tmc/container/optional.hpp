// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Optional value, with C++26 API <optional> fulfils every requirement of a container

#include <optional> // std::optional<>


namespace tmc {

template <class T>
using optional = std::optional<T>;

using nullopt_t = std::nullopt_t;

constexpr nullopt_t nullopt = std::nullopt;

// Note: With C++26 additions `std::optional` fulfils every requirement of a "full" optional API,
//       before that `boost::optional` or Beman's project implementation can be used instead. For
//       now we leave it a stub API for possible future replacement.

} // namespace tmc
