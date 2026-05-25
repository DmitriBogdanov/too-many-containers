// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // true_type
#include <utility>     // forward()

#include <tmc/macro/no_discard.hpp>

namespace tmc::projections {

struct identity {
    
    template <class T>
    TMC_NO_DISCARD constexpr decltype(auto) operator()(T&& value) const noexcept {
        return std::forward<T>(value);
    }

    using is_transparent = std::true_type;
    
};

} // namespace tmc::projections
