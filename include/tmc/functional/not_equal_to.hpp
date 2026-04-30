// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/functional/not_equal.hpp>
#include <tmc/functional/singular_closure.hpp>

namespace tmc {

template <class T>
struct not_equal_to : singular_closure<T> {
    
    template <class Arg>
    constexpr decltype(auto) operator()(const Arg& arg)
        noexcept(tmc::not_equal{}(arg, this->value))
    {
        return tmc::not_equal{}(arg, this->value);
    }
    
};

template <class T>
not_equal_to(T&&) -> not_equal_to<T>;
    
} // namespace tmc
