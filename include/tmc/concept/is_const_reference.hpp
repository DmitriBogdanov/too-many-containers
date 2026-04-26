// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_reference_v<>, is_const_v<>, remove_reference_t<>

namespace tmc {

template <class T>
concept is_const_reference = std::is_reference_v<T> and std::is_const_v<std::remove_reference_t<T>>;

} // namespace tmc
