// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Transparent hasher

#include <functional>  // std::hash<>
#include <type_traits> // std::remove_cvref_t<>
#include <utility>     // std::forward<>()


namespace tmc {

struct hash {
    using is_transparent = std::true_type;

    template <class T>
    [[nodiscard]] constexpr std::size_t operator()(T&& value) const noexcept {
        return std::hash<std::remove_cvref_t<T>>{}(std::forward<T>(value));
    }
};

} // namespace tmc
