// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>
#include <utility>  // forward()

#include <tmc/macro/no_discard.hpp>
#include <tmc/requirement/is_nothrow_convertible.hpp>

namespace tmc::projections {

template <class T>
struct cast {

    template <class Arg>
        requires std::convertible_to<Arg, T>
    TMC_NO_DISCARD constexpr auto operator()(Arg&& arg) const
        noexcept(is_nothrow_convertible<Arg, T>)
    {
        return static_cast<T>(std::forward<Arg>(arg));
    }
    
};

} // namespace tmc::projections
