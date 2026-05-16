// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_nothrow_convertible_v<>

namespace tmc {

template <class T, class... Args>
concept is_nothrow_convertible = std::is_nothrow_convertible_v<T, Args...>;

} // namespace tmc
