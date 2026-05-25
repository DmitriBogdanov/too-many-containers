// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ranges> // ranges::iterator_t<>

#include <tmc/concept/has_erase.hpp>

namespace tmc {

template <class R, class... Args>
concept has_erase_range = has_erase<R, std::ranges::iterator_t<R>, std::ranges::iterator_t<R>>;

} // namespace tmc
