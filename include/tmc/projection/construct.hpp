// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts> // constructible_from<>
#include <utility>  // forward()

#include <tmc/macro/no_discard.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>

namespace tmc {

template <class To>
struct construct {

    template <class From>
        requires std::constructible_from<To, From>
    TMC_NO_DISCARD constexpr auto operator()(From&& value)
        noexcept(is_nothrow_constructible<From, To>)
    {
        return static_cast<To>(std::forward<From>(value));
    }
    
};

} // namespace tmc
