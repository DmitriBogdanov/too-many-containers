// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_copy_assignable_v<>

namespace tmc {

template <class T>
concept is_copy_assignable = std::is_copy_assignable_v<T>;

} // namespace tmc
