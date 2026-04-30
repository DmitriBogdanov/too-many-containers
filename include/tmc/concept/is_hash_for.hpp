// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>    // regular_invocable<>, convertible_to<>
#include <cstddef>     // size_t
#include <type_traits> // invoke_result_t<>

namespace tmc {

template <class Hash, class T>
concept is_hash_for =
    std::regular_invocable<Hash, T> and std::convertible_to<std::invoke_result_t<Hash, T>, std::size_t>;

} // namespace tmc
