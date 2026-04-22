// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Vector container

#include <vector> // std::vector<>

#include <tmc/memory/allocator.hpp> // tmc::allocator<>


namespace tmc {

template <class T, class Alloc = tmc::allocator<T>>
using vector = std::vector<T, Alloc>;

} // namespace tmc
