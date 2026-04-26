// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/concept/is_void.hpp>

namespace tmc {

template <class T>
concept is_non_void = not is_void<T>;
    
} // namespace tmc
