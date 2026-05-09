// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#include <common/framework.hpp>

#include <tmc/projection/bind.hpp>

namespace {

    constexpr int square(int x) noexcept { return x * x; }
    
} // namespace

TEST_CASE("Binding free function to a type") {
    using squaring_projection = tmc::projections::bind<square>;
    
    static_assert(squaring_projection{}(5) == 25);
}
