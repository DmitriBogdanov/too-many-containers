// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/concept/is_arithmetic.hpp>
#include <tmc/macro/no_discard.hpp>

namespace tmc {

template <is_arithmetic R, is_arithmetic L>
TMC_NO_DISCARD constexpr auto absdiff(R lhs, L rhs) noexcept {
    const auto common_lhs = static_cast<std::common_type_t<R, L>>(lhs);
    const auto common_rhs = static_cast<std::common_type_t<R, L>>(rhs);
    
    return (common_lhs > common_rhs) ? (common_lhs - common_rhs) : (common_rhs - common_lhs);
}

} // namespace tmc
