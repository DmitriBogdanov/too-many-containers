// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

namespace tmc {

struct divides {
    
    template <class L, class R>
    constexpr decltype(auto) operator()(L&& lhs, R&& rhs) const
        noexcept(noexcept(std::forward<L>(lhs) / std::forward<R>(rhs)))
    {
        return std::forward<L>(lhs) / std::forward<R>(rhs);
    }
    
};

// Note: This could be an alias to `std::divides<>`. Re-implementation is motivated by compile times.
//       <utility> is very lightweight, ~10-20 times faster than including <functional>.

} // namespace tmc
