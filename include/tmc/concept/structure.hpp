// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Constraints for structures & classes

#include <concepts> // std::convertible_to<>
#include <tuple>    // std::make_tuple(), std::tuple<>
#include <utility>  // std::forward()
#include <type_traits> // std::is_aggregate_v<>


namespace tmc::req::detail {

// Concept-checking whether a type can be decomposed with structured binding is not possible to implement in
// the general case, but it is implementable for a specific size by checking whether binding expression compiles.
//
// Since we cannot use structured binding in the concept directly, we have to write a free function decomposing
// the value with structure binding and force the compiler to evaluate its body eagerly by returning `auto`.
//
template <class T, class U1, class U2>
[[nodiscard]] constexpr auto eager_decompose_pair(T&& pair) {
    auto&& [lhs, rhs] = std::forward<T>(pair);
    return std::make_tuple(lhs, rhs);
}

} // namespace tmc::req::detail


namespace tmc::req {

template <class S, class U1, class U2 = U1>
concept decomposable_pair = requires(S&& value) {
    { detail::eager_decompose_pair<S, U1, U2>(std::forward<S>(value)) } -> std::convertible_to<std::tuple<U1, U2>>;
};

template <class T>
concept aggregate = std::is_aggregate_v<T>;

template <class T>
concept trivially_default_constructible = std::is_trivially_default_constructible_v<T>;

template <class T, class... Args>
concept trivially_constructible = std::is_trivially_constructible_v<T, Args...>;

template <class T>
concept trivially_copyable = std::is_trivially_copyable_v<T>;

} // namespace tmc::req
