// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

#include <tmc/macro/no_discard.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>
#include <tmc/utility/tuple.hpp>

namespace tmc {

// A strongly typed tuple of forwarded references.
// 
// We want this to be a distinct type in order to disambiguate cases that
// forward multiple arguments to a class that can be constructed from a tuple.
// 
// R-value references should be captured as values to avoid dangling:
//
//    emplace_args{ ... <  const reference> ... } -> emplace_args< ... const T& ... >
//    emplace_args{ ... <l-value reference> ... } -> emplace_args< ...       T& ... >
//    emplace_args{ ... <r-value reference> ... } -> emplace_args< ...       T  ... >
//    emplace_args{ ... <            value> ... } -> emplace_args< ...       T  ... >
//
template <class... Args>
struct emplace_args {
    using value_type = tmc::tuple<Args...>;
    
    value_type value;
    
    constexpr emplace_args(Args&&... args)
        noexcept(is_nothrow_constructible<value_type, Args...>)
    :
        value(std::forward<Args>(args)...) {}
};

template <class... Args>
emplace_args(Args&&...) -> emplace_args<Args...>;

// Factory function for stylistic uniformity with standard APIs, doesn't
// do much since `emplace_args{ ... }` would already be valid by itself.
//
template <class... Args>
TMC_NO_DISCARD constexpr auto make_emplace_args(Args&&... args)
    noexcept (is_nothrow_constructible<emplace_args<Args...>, Args...>)
{
    return emplace_args<Args...>{ std::forward<Args>(args)... };
}

} // namespace tmc
