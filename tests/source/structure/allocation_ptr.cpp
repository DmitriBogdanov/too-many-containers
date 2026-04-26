// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

// Content: `tmc::allocation_ptr<>` tests

#include <common/framework.hpp>

#include <array> // std::array<>

#include <tmc/structure/allocation_ptr.hpp> // tmc::allocation_ptr<>


TEST_CASE("allocation_ptr<T> type properties") {
    using array_type = std::array<std::uint64_t, 64>;
    using alloc_type = tmc::allocator<array_type>;

    // Stateless allocators should not affect object size
    static_assert(sizeof(tmc::allocation_ptr<array_type>) == sizeof(std::unique_ptr<array_type>));
    
    // Pointer should be move-only
    static_assert(not std::copyable<tmc::allocation_ptr<array_type>>);
    static_assert(std::movable<tmc::allocation_ptr<array_type>>);
    
    // Move should be non-throwing
    static_assert(tmc::req::nothrow_move_constructible<tmc::allocation_ptr<array_type>>);
    
    // `allocate_unique()` should return appropriate type
    auto ptr = tmc::allocate_unique<array_type>(alloc_type{});

    static_assert(std::same_as<decltype(ptr), tmc::allocation_ptr<array_type, alloc_type>>);
}
