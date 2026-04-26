// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

namespace tmc {

template <class R, class T>
concept has_push = requires(R range, T arg) {
    range.push(arg);
};
    
} // namespace tmc
