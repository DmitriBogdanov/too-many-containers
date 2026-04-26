// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

namespace tmc {

template <class R, class... Args>
concept has_insert = requires(R range, Args&&... args) {
    range.insert(std::forward<Args>(args)...);
};

} // namespace tmc
