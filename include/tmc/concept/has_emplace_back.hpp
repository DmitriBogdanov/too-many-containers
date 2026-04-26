// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

namespace tmc {

template <class R, class... Args>
concept has_emplace_back = requires(R range, Args&&... args) {
    range.emplace_back(std::forward<Args>(args)...);
};

} // namespace tmc
