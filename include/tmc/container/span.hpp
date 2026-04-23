// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Span container

#include <span>        // std::span<>, std::size_t, std::dynamic_extent
#include <type_traits> // std::remove_const_t<>, std::add_const_t<>


namespace tmc {

template <class T, std::size_t extent = std::dynamic_extent>
using span = std::span<T, extent>;

// Shortcuts for mutable / const versions
template <class T, std::size_t extent = std::dynamic_extent>
using lspan = tmc::span<std::remove_const_t<T>, extent>;

template <class T, std::size_t extent = std::dynamic_extent>
using cspan = tmc::span<std::add_const_t<T>, extent>;

} // namespace tmc
