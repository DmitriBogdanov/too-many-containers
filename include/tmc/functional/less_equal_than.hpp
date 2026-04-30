// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/functional/less_equal.hpp>
#include <tmc/functional/singular_closure.hpp>

namespace tmc {

template <class T>
struct less_equal_than : singular_closure<T> {
    
    template <class Arg>
    constexpr decltype(auto) operator()(const Arg& arg)
        noexcept(tmc::less_equal{}(arg, this->value))
    {
        return tmc::less_equal{}(arg, this->value);
    }
    
};

template <class T>
less_equal_than(T&&) -> less_equal_than<T>;
    
} // namespace tmc
