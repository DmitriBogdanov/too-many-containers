// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_const_v<>, is_volatile_v<>

namespace tmc {

template <class T>
concept is_cv_unqualified = not std::is_const_v<T> and not std::is_volatile_v<T>;

} // namespace tmc
