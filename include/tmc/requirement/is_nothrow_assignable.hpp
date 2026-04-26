// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_nothrow_assignable_v<>

namespace tmc {

template <class T, class Arg>
concept is_nothrow_assignable = std::is_nothrow_assignable_v<T, Arg>;

} // namespace tmc
