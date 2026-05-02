// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

namespace tmc {

template <class R, class... Args>
concept has_nothrow_try_emplace = requires(R range, Args&&... args) {
    { range.try_emplace(std::forward<Args>(args)...) } noexcept;
};

} // namespace tmc
