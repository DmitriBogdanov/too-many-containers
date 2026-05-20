// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // constructible_from<>

namespace tmc {

template <class T>
concept is_explicitly_copyable = std::constructible_from<T, const T&>;

} // namespace tmc
