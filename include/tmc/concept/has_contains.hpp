// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>

namespace tmc {

template <class R, class K>
concept has_contains = requires(R range, K key) {
    { range.contains(key) } -> std::convertible_to<bool>;
};

} // namespace tmc
