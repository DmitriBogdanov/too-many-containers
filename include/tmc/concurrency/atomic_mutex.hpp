// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <atomic> // atomic_flag, memory_order

namespace tmc {

// Tiny (single-byte) mutex based on C++20 atomic wait.
//
// Extremely cheap in uncontested case, for cases with high contention
// prefer classic mutexes that ensure fair thread priority during wake.
//
// Note that outside of unusual platforms that implement atomic waiting as a busy spin
// this is NOT a spinlock, e.g. libc++ spins polling for ~4 microseconds then switches
// to a platform-specific global waiting table, effectively acting as a tiny futex, see:
// https://github.com/llvm/llvm-project/blob/release/22.x/libcxx/include/__atomic/atomic_sync.h
//
class atomic_mutex {
    std::atomic_flag flag = {};

public:

    bool try_lock() noexcept {
        return not this->flag.test_and_set(std::memory_order_acquire);
    }

    void lock() noexcept {
        while (this->flag.test_and_set(std::memory_order_acquire))
            this->flag.wait(true, std::memory_order_relaxed);
    }

    void unlock() noexcept {
        this->flag.clear(std::memory_order_release);
        
        this->flag.notify_one();
    }

};

} // namespace tmc
