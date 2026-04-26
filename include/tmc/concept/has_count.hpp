// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // integral

namespace tmc {

template <class R, class K>
concept has_count = requires(R range, K key) {
    { range.count(key) } -> std::integral;
};

} // namespace tmc
