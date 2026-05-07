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
#include <tmc/concept/is_void.hpp>
#include <tmc/container/optional.hpp>
#include <tmc/requirement/is_nothrow_constructible.hpp>
#include <tmc/requirement/is_nothrow_invocable.hpp>

namespace tmc {

template <class Func, class... Args>
class try_invoke_result {
    using invoke_result = std::invoke_result_t<Func, Args...>;
public:
    using type = std::conditional_t<is_void<invoke_result>, bool, optional<invoke_result>>;
};

template <class Func, class... Args>
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
    
    if constexpr (not is_boolean_testable<Func>)
        return result_type{ std::invoke(func, std::forward<Args>(args)...) };
    
    if (func)
        return result_type{ std::invoke(func, std::forward<Args>(args)...) };

    return result_type{};
}

} // namespace tmc
