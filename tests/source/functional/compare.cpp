// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

// Content:

#include <common/framework.hpp>

#include <tmc/functional/compare.hpp> // tmc::less,


TEST_CASE("Transparent comparators") {
    
    static_assert(tmc::less{}(2, 3));
    
}
