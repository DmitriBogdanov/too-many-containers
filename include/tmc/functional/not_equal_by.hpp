// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <functional> // invoke()

#include <tmc/functional/not_equal.hpp>
#include <tmc/functional/singular_closure.hpp>

namespace tmc {

template <class Proj>
struct not_equal_by : singular_closure<Proj> {

    template <class L, class R>
    constexpr decltype(auto) operator()(L&& lhs, R&& rhs) const
        noexcept(noexcept(
            tmc::not_equal{}(std::invoke(this->value, std::forward<L>(lhs)), std::invoke(this->value, std::forward<R>(rhs)))
        ))
    {
        return tmc::not_equal{}(std::invoke(this->value, std::forward<L>(lhs)), std::invoke(this->value, std::forward<R>(rhs)));
    }

};

template <class Proj>
not_equal_by(Proj&&) -> not_equal_by<Proj>;

} // namespace tmc
