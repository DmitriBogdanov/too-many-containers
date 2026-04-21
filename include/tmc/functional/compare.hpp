// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Transparent comparator functors

#include <functional> // std::equal_to<>, std::greater<>, std::less<>, ...


namespace tmc {

using     equal_to  = std::    equal_to <>;
using not_equal_to  = std::not_equal_to <>;
using greater       = std::greater      <>;
using greater_equal = std::greater_equal<>;
using    less       = std::   less      <>;
using    less_equal = std::   less_equal<>;
    
} // namespace tmc
