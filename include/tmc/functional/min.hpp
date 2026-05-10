// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <utility> // forward()

#include <tmc/functional/less.hpp>

namespace tmc {

struct min {
    
    template <class L, class R>
    constexpr decltype(auto) operator()(L&& lhs, R&& rhs) const
        noexcept(noexcept(tmc::less{}(lhs, rhs) ? std::forward<L>(lhs) : std::forward<R>(rhs)))
    {
        return tmc::less{}(lhs, rhs) ? std::forward<L>(lhs) : std::forward<R>(rhs);
    }
    
};

} // namespace tmc
