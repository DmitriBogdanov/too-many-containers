// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <atomic> // atomic_flag, memory_order

namespace tmc {

// Spinlock mutex (busy-waiting mutex).
//
// Cheapest possible implementation of a mutex in uncontested case. Under contention has
// the lowest locking / unlocking latency at the cost of burning CPU cycles on busy wait.
//
// NOT recommended for general usage. This is a tool for special cases
// such as extremely low contention workloads with short locking periods.
//
class spin_mutex {
    std::atomic_flag flag = {};

public:

    bool try_lock() noexcept {
        return not this->flag.test_and_set(std::memory_order_acquire);
    }

    void lock() noexcept {
        while (this->flag.test_and_set(std::memory_order_acquire)) {}
    }

    void unlock() noexcept {
        this->flag.clear(std::memory_order_release);
    }
    
};

} // namespace tmc
