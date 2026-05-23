// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

namespace tmc {

// Equivalent of `std::ignore` that also supports
// invocation, use to explicitly discard return values
struct ignore_t {

    constexpr static void operator()([[maybe_unused]] auto&&...) noexcept {}


    constexpr const ignore_t& operator=([[maybe_unused]] auto&&) const noexcept { return *this; }
    
};

inline constexpr auto ignore = ignore_t{};

} // namespace tmc
