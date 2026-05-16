// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <atomic>  // atomic_ref<>
#include <utility> // forward()

#include <tmc/macro/no_discard.hpp>

namespace tmc::projections {

struct atomic {

    template <class T>
    TMC_NO_DISCARD constexpr auto operator()(T&& value) noexcept {
        return std::atomic_ref{ std::forward<T>(value) };
    }

};

} // namespace tmc::projections
