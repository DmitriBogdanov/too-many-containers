// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <functional>  // hash<>, size_t
#include <type_traits> // remove_reference_t<>, true_type
#include <utility>     // forward()

#include <tmc/concept/is_hash_for.hpp>
#include <tmc/macro/no_discard.hpp>

namespace tmc {

struct hash {

    template <class T>
        requires is_hash_for<std::remove_reference_t<T>, T>
    TMC_NO_DISCARD constexpr std::size_t operator()(T&& arg) const noexcept {
        return std::hash<std::remove_reference_t<T>>{}(std::forward<T>(arg));
    }

    using is_transparent = std::true_type;
    
};

// Note: Custom hash could be implemented, but since `std::hash` is a standard customization point,
//       replacing it with independent implementation would cause too much practical friction.

} // namespace tmc
