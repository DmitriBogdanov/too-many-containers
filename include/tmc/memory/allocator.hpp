// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Default TMC allocator

#include <memory> // std::allocator<>


namespace tmc {

template <class T>
using allocator = std::allocator<T>;

} // namespace tmc
