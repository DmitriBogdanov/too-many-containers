// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/functional/equal.hpp>
#include <tmc/functional/singular_closure.hpp>

namespace tmc {

template <class T>
struct equal_to : singular_closure<T> {
    
    template <class Arg>
    constexpr decltype(auto) operator()(const Arg& arg)
        noexcept(tmc::equal{}(arg, this->value))
    {
        return tmc::equal{}(arg, this->value);
    }
    
};

template <class T>
equal_to(T&&) -> equal_to<T>;
    
} // namespace tmc
