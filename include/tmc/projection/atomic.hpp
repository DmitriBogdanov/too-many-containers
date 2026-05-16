// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <atomic> // atomic_ref<>

#include <tmc/macro/no_discard.hpp>

namespace tmc::projections {

struct atomic {
    
    template <class T>
    TMC_NO_DISCARD constexpr decltype(auto) operator()(const T& value) const noexcept {
        return value; // const references are inherently thread-safe, just forward them
    }
    
    template <class T>
    TMC_NO_DISCARD constexpr decltype(auto) operator()(T& value) const noexcept {
        return std::atomic_ref{ value };
    }

};

} // namespace tmc::projections
