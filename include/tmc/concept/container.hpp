// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Constraints for detecting container API

#include <concepts> // std::convertible_to<>
#include <ranges>   // std::ranges::iterator_t<>


namespace tmc::req {

template <class R, class K>
concept provides_find_for = requires(R range, K key) {
    { range.find(key) } -> std::convertible_to<std::ranges::iterator_t<R>>;
};

template <class R, class K>
concept provides_contains_for = requires(R range, K key) {
    { range.contains(key) } -> std::convertible_to<bool>;
};

template <class R, class K>
concept provides_count_for = requires(R range, K key) {
    { range.contains(key) } -> std::integral;
};

template <class R, class K, class V>
concept provides_at_for = requires(R range, K key) {
    { range.at(key) } -> std::convertible_to<V>;
};

template <class R, class K, class V>
concept provides_bracket_operator_for = requires(R range, K key) {
    { range[key] } -> std::convertible_to<V>;
};

template <class R, class K, class V>
concept provides_equal_range_for = requires(R range, K key) {
    { range.equal_range(key) } -> std::convertible_to<V>;
};

template <class R, class... Args>
concept provides_emplace_for = requires(R range, Args&&... args) {
    range.emplace(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_try_emplace_for = requires(R range, Args&&... args) {
    range.try_emplace(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_emplace_back_for = requires(R range, Args&&... args) {
    range.emplace_back(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_emplace_front_for = requires(R range, Args&&... args) {
    range.emplace_front(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_insert_for = requires(R range, Args&&... args) {
    range.insert(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_push_back_for = requires(R range, Args&&... args) {
    range.push_back(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_push_front_for = requires(R range, Args&&... args) {
    range.push_front(std::forward<Args>(args)...);
};

template <class R, class... Args>
concept provides_erase_for = requires(R range, Args&&... args) {
    range.erase(std::forward<Args>(args)...);
};

template <class R, class S = std::size_t>
concept provides_resize = requires(R range, S size) {
    range.resize(size);
};

template <class R, class S = std::size_t>
concept provides_reserve = requires(R range, S capacity) {
    range.resize(capacity);
};

} // namespace tmc::req
