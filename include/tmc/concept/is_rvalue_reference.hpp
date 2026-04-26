// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_rvalue_reference_v<>

namespace tmc {

template <class T>
concept is_rvalue_reference = std::is_rvalue_reference_v<T>;

} // namespace tmc
