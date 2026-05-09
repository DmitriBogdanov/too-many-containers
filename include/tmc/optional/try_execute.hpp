// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>    // invocable<>
#include <functional>  // invoke()
#include <ranges>      // ranges::input_range<>, ranges::empty()
#include <type_traits> // conditional_t<>
#include <utility>     // forward()

#include <tmc/concept/is_non_void.hpp>
#include <tmc/container/optional.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>
#include <tmc/requirement/is_nothrow_invocable.hpp>

namespace tmc {

template <class Func, class Range, class... Args>
    requires std::ranges::input_range<Range> and std::invocable<Func, Range, Args...>
class try_execute_result {
    using invoke_result = std::invoke_result_t<Func, Range, Args...>;
public:
    using type = std::conditional_t<is_non_void<invoke_result>, optional<invoke_result>, bool>;
};

template <class Func, class Range, class... Args>
    requires std::ranges::input_range<Range> and std::invocable<Func, Range, Args...>
using try_execute_result_t = try_execute_result<Func, Range, Args...>::type;

// Attempt to invoke function object `func` that operates on non-empty `range` and 
// forward its return value as an optional (or `bool` for functions that return `void`).
//
// Use case: Invoking algorithms on potentially empty ranges, e.g.:
//
//    > const auto max = tmc::try_execute(std::ranges::max, range).value_or(0);
//
template <class Func, class Range, class... Args>
    requires std::ranges::input_range<Range> and std::invocable<Func, Range, Args...>
constexpr try_execute_result_t<Func, Range, Args...> try_execute(Func&& func, Range&& range, Args&&... args)
    noexcept(
        is_nothrow_invocable<Func, Range, Args...> and
        is_nothrow_constructible<try_execute_result_t<Func, Range, Args...>, std::invoke_result_t<Func, Range, Args...>>
    )
{
    using result_type = try_execute_result_t<Func, Range, Args...>;
    
    if (std::ranges::empty(range)) return result_type{};
    
    if constexpr (is_non_void<std::invoke_result_t<Func, Range, Args...>>)
        return result_type{ std::invoke(func, std::forward<Range>(range), std::forward<Args>(args)...) };
    else
        return (std::invoke(func, std::forward<Range>(range), std::forward<Args>(args)...), true);
}
    
} // namespace tmc
