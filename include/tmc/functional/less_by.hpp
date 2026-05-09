// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <functional> // invoke()

#include <tmc/functional/less.hpp>
#include <tmc/functional/singular_closure.hpp>

namespace tmc {

template <class Proj>
struct less_by : singular_closure<Proj> {

    template <class L, class R>
    constexpr decltype(auto) operator()(L&& lhs, R&& rhs) const
        noexcept(noexcept(
            tmc::less{}(std::invoke(this->value, std::forward<L>(lhs)), std::invoke(this->value, std::forward<R>(rhs)))
        ))
    {
        return tmc::less{}(std::invoke(this->value, std::forward<L>(lhs)), std::invoke(this->value, std::forward<R>(rhs)));
    }

};

template <class Proj>
less_by(Proj&&) -> less_by<Proj>;

} // namespace tmc
