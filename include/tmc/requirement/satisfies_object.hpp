// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/concept/is_reference.hpp>

namespace tmc {

// Unnamed requirement `Object`, see https://en.cppreference.com/cpp/language/object
//
// Note that array types (e.g. `int[]`) and incomplete types (e.g. `struct some_type;`)
// are NOT considered to be objects since they have no size or alignment.
//
template <class T>
concept satisfies_object = bool(sizeof(T)) and bool(alignof(T)) and not is_reference<T>;

} // namespace tmc
