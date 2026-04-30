// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/functional/greater.hpp>
#include <tmc/functional/singular_closure.hpp>

namespace tmc {

template <class T>
struct greater_than : singular_closure<T> {
    
    template <class Arg>
    constexpr decltype(auto) operator()(const Arg& arg)
        noexcept(tmc::greater{}(arg, this->value))
    {
        return tmc::greater{}(arg, this->value);
    }
    
};

template <class T>
greater_than(T&&) -> greater_than<T>;
    
} // namespace tmc
