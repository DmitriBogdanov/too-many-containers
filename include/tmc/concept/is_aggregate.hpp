// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits>  // is_aggregate_v<>

namespace tmc {

template <class T>
concept is_aggregate = std::is_aggregate_v<T>;
    
} // namespace tmc
