// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // true_type
#include <utility>     // forward()

namespace tmc {

struct equal {
    
    template <class L, class R>
    constexpr decltype(auto) operator()(L&& lhs, R&& rhs) const 
        noexcept(noexcept(std::forward<L>(lhs) == std::forward<R>(rhs)))
    {
        return std::forward<L>(lhs) == std::forward<R>(rhs);
    }

    using is_transparent = std::true_type;
    
};

// Note: This could be an alias to `std::equal_to<>`. Re-implementation is motivated by compile times.
//       <type_traits> + <utility> are very lightweight, ~10 times faster than including <functional>.

} // namespace tmc
