// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // convertible_to<>
#include <utility>  // forward()

#include <tmc/macro/no_discard.hpp>
#include <tmc/requirement/is_nothrow_convertible.hpp>

namespace tmc {

template <class To>
struct cast {

    template <class From>
        requires std::convertible_to<From, To>
    TMC_NO_DISCARD constexpr auto operator()(From&& value)
        noexcept(is_nothrow_convertible<From, To>)
    {
        return static_cast<To>(std::forward<From>(value));
    }
    
};

} // namespace tmc
