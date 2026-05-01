// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // is_nothrow_invocable_v<>

namespace tmc {

template <class T, class... Args>
concept is_nothrow_invocable = std::is_nothrow_invocable_v<T, Args...>;

} // namespace tmc
