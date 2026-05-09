// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef> // size_t

#include <tmc/concept/can_adl_get.hpp>
#include <tmc/macro/no_discard.hpp>

namespace tmc::projections {

template <std::size_t index>
struct element {

    template <class T>
        requires can_adl_get<T, index>
    TMC_NO_DISCARD constexpr decltype(auto) operator()(T&& value)
        noexcept(noexcept(get<index>(value)))
    {
        return get<index>(value);
    }
    
};

} // namespace tmc::projections
