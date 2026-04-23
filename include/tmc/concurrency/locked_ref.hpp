// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Reference type that hold the lock for its lifetime

#include <concepts> // std::constructible_from<>
#include <mutex>    // std::mutex, std::scoped_lock

#include <tmc/concept/structure.hpp> // tmc::req


namespace tmc {

// Reference that locks the underlying value for its lifetime, in a way it can be
// interpreted as an `std::atomic_ref<>` replacement usable for non-atomic objects.
template <class T, class Guard>
struct locked_ref {
    using value_type = T;
    using guard_type = Guard;

    using reference = value_type&;
    using pointer   = value_type*;

private:
    reference  value;
    guard_type guard;

public:
    template <class... Args>
        requires std::constructible_from<guard_type, Args...>
    locked_ref(reference value, Args&&... args) noexcept(req::nothrow_constructible<guard_type, Args...>)
        : value(value), guard(std::forward<Args>(args)...) {}

    // Reference is non-nullable and cannot be rebound
    locked_ref() = delete;

    locked_ref(const locked_ref&) = delete;
    locked_ref(locked_ref&&)      = delete;

    locked_ref& operator=(const locked_ref&) = delete;
    locked_ref& operator=(locked_ref&&)      = delete;

    // Assignment works with the underlying object
    template <class Arg>
    locked_ref& operator=(Arg&& arg) noexcept(req::nothrow_assignable<reference, Arg>)
        requires req::assignable<reference, Arg>
    {
        this->value = std::forward<Arg>(arg);

        return *this;
    }

    // Access
    [[nodiscard]] reference get() const noexcept { return this->value; }

    operator reference() const noexcept { return this->value; }

    pointer operator->() const noexcept { return std::addressof(this->value); }
};

// By default CTAD should deduce a scoped lock over all passed mutexes,
// for arbitrary lock types with arbitrary arguments (e.g. lock policies)
// full parameters should be specified instead.
template <class T, class... Args>
locked_ref(T&, Args...) -> locked_ref<T, std::scoped_lock<Args...>>;

} // namespace tmc
