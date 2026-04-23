// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Constraints for structures & classes

#include <concepts>    // std::convertible_to<>
#include <tuple>       // std::make_tuple(), std::tuple<>
#include <type_traits> // std::is_aggregate_v<>, std::is_trivially_default_constructible_v<>, ...
#include <utility>     // std::forward()


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

template <class T>
concept default_constructible = std::is_default_constructible_v<T>;

template <class T>
concept copy_constructible = std::is_copy_constructible_v<T>;

template <class T>
concept move_constructible = std::is_move_constructible_v<T>;

template <class T, class Args>
concept assignable = std::is_assignable_v<T, Args>;

template <class T>
concept copy_assignable = std::is_copy_assignable_v<T>;

template <class T>
concept move_assignable = std::is_move_assignable_v<T>;

template <class T>
concept nothrow_default_constructible = std::is_nothrow_default_constructible_v<T>;

template <class T, class... Args>
concept nothrow_constructible = std::is_nothrow_constructible_v<T, Args...>;

template <class T>
concept nothrow_copy_constructible = std::is_nothrow_copy_constructible_v<T>;

template <class T>
concept nothrow_move_constructible = std::is_nothrow_move_constructible_v<T>;

template <class T>
concept nothrow_copy_assignable = std::is_nothrow_copy_assignable_v<T>;

template <class T>
concept nothrow_move_assignable = std::is_nothrow_move_assignable_v<T>;

template <class T, class Arg>
concept nothrow_assignable = std::is_nothrow_assignable_v<T, Arg>;

template <class T>
concept transparent = requires { typename T::is_transparent; };
// this annotation signifies transparent hashes and comparators

template <class T>
concept avalanching = requires { typename T::is_avalanching; };
// this annotation signifies hashes with avalanching effect (any change
// in the input bits has a 50/50 chance to flip all bits of the hash)

} // namespace tmc::req
