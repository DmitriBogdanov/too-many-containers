// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>    // invocable<>
#include <functional>  // invoke()
#include <type_traits> // conditional_t<>
#include <utility>     // forward()

#include <tmc/concept/is_bool_testable.hpp>
#include <tmc/concept/is_non_void.hpp>
#include <tmc/container/optional.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>
#include <tmc/requirement/is_nothrow_invocable.hpp>

namespace tmc {

template <class Func, class... Args>
    requires std::invocable<Func, Args...>
class try_invoke_result {
    using invoke_result = std::invoke_result_t<Func, Args...>;
public:
    using type = std::conditional_t<is_non_void<invoke_result>, optional<invoke_result>, bool>;
};

template <class Func, class... Args>
    requires std::invocable<Func, Args...>
using try_invoke_result_t = try_invoke_result<Func, Args...>::type;

// Attempt to invoke function object `func` with `args...` and forward its
// return value as an optional (or `bool` for functions that return `void`).
//
// Use case: Invoking potentially nullable function objects, e.g. `std::function`:
//
//    > const auto value = tmc::try_invoke(func, arg).value_or(0);
//
template <class Func, class... Args>
    requires std::invocable<Func, Args...>
constexpr try_invoke_result_t<Func, Args...> try_invoke(Func&& func, Args&&... args)
    noexcept(
        is_nothrow_invocable<Func, Args...> and
        is_nothrow_constructible<try_invoke_result_t<Func, Args...>, std::invoke_result_t<Func, Args...>>
    )
{
    using result_type = try_invoke_result_t<Func, Args...>;
    
    constexpr bool requires_test = is_boolean_testable<Func>;
    constexpr bool returns_value = is_non_void<std::invoke_result_t<Func, Args...>>;
    
    if constexpr (requires_test) {
        if constexpr (returns_value)
            return func ? result_type{ std::invoke(func, std::forward<Args>(args)...) } : result_type{};
        else
            return func ? (std::invoke(func, std::forward<Args>(args)...), true) : false;
    }
    else {
        if constexpr (returns_value)
            return result_type{ std::invoke(func, std::forward<Args>(args)...) };
        else
            return (std::invoke(func, std::forward<Args>(args)...), true);
    }
}

} // namespace tmc
