// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>   // invocable<>
#include <functional> // invoke()
#include <utility>    // forward()

namespace tmc::projections {

// Binds free function to a type.
// 
// Note: While not the main purpose, in many cases binding free function
//       to a type before passing it into an algorithm aids in inlining,
//       compilers often struggle to inline through function pointers.
//
template <auto function>
struct bind {
    
    template <class... Args>
        requires std::invocable<decltype(function), Args...>
    constexpr decltype(auto) operator()(Args&&... args) const
        noexcept(noexcept(std::invoke(function, std::forward<Args>(args)...)))
    {
        return std::invoke(function, std::forward<Args>(args)...);
    }
    
};

} // namespace tmc::projections
