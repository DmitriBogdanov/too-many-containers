// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <algorithm> // ranges::move(), ranges::copy()
#include <concepts>  // constructible_from<>
#include <iterator>  // indirectly_movable<>, indirectly_copyable<>
#include <ranges>    // ranges::range<>, ranges::range_adaptor_closure<>, ranges::iterator_t<>, ranges::begin()
#include <utility>   // forward()

#include <tmc/requirement/is_nothrow_constructible.hpp>

namespace tmc::ranges {

// Closure that moves/copies contents of the piped range into its captured range. 
//
// Can be used to construct fixed-size containers which is not possible with `std::ranges::to`, e.g.:
//
//    > auto array = range | tmc::ranges::store{ std::array<int, 8>{} }; // returns captured value
//
// Alternatively, can be used to store things into an existing range at the end of the pipe:
//
//    > std::vector<int> vector(8);
//    >
//    > auto& ref = range | tmc::ranges::store{ vector }; // returns captured reference
//
template <std::ranges::range T>
class store : public std::ranges::range_adaptor_closure<store<T>> {

    T target;

public:

    template <class... Args>
        requires std::constructible_from<T, Args...>
    constexpr store(Args&&... arg)
        noexcept(is_nothrow_constructible<T, Args...>)
    :
        target(std::forward<T>(arg)...)
    {}

    template <class R>
        requires
        std::indirectly_movable <std::ranges::iterator_t<R>, std::ranges::iterator_t<T>> or
        std::indirectly_copyable<std::ranges::iterator_t<R>, std::ranges::iterator_t<T>>
    constexpr decltype(auto) operator()(R&& range) {
        constexpr bool can_move = std::indirectly_movable <std::ranges::iterator_t<R>, std::ranges::iterator_t<T>>;
        constexpr bool can_copy = std::indirectly_copyable<std::ranges::iterator_t<R>, std::ranges::iterator_t<T>>;

        if constexpr (can_move) std::ranges::move(std::forward<R>(range), std::ranges::begin(this->target));
        if constexpr (can_copy) std::ranges::copy(std::forward<R>(range), std::ranges::begin(this->target));

        return this->target;
    }
    
};

template <class T>
store(T&&) -> store<T>;

} // namespace tmc::ranges
