// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // constructible_from<>
#include <utility>  // forward()

#include <tmc/macro/no_discard.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>

namespace tmc::projections {

template <class T>
struct construct {

    template <class Arg>
        requires std::constructible_from<T, Arg>
    TMC_NO_DISCARD constexpr auto operator()(Arg&& arg) const
        noexcept(is_nothrow_constructible<Arg, T>)
    {
        return static_cast<T>(std::forward<Arg>(arg));
    }
    
};

} // namespace tmc::projections
