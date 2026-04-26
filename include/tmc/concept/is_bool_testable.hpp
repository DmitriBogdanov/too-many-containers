// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // constructible_from<>

namespace tmc {

template <class T>
concept is_boolean_testable = std::constructible_from<bool, T>;
// this is satisfied when `T` is explicitly convertible to `bool` => can
// be used in boolean test expression (e.g. `if (cond)`), this is a weaker
// requirement than a seemingly more intuitive `std::convertible_to<bool>`

} // namespace tmc
