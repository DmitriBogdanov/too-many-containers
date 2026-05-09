// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // conditional_t<>, declval()
#include <utility>     // move()

#include <tmc/concept/has_empty.hpp>
#include <tmc/concept/has_front.hpp>
#include <tmc/concept/has_pop.hpp>
#include <tmc/concept/has_top.hpp>
#include <tmc/concept/is_always_false.hpp>
#include <tmc/container/optional.hpp>

namespace tmc::detail {

template <class C> concept is_stack = has_empty<C> and has_pop<C> and not has_front<C> and     has_top<C>;
template <class C> concept is_queue = has_empty<C> and has_pop<C> and     has_front<C> and not has_top<C>;

} // namespace tmc::detail


namespace tmc {

template <class C>
struct try_pop_result {
    static_assert(is_always_false<C>, "Invalid instantiation of `tmc::try_pop_result`");
};

template <detail::is_stack C>
struct try_pop_result<C> {
    using type = optional<std::remove_reference_t<decltype(std::declval<C>().top())>>;
};

template <detail::is_queue C>
struct try_pop_result<C> {
    using type = optional<std::remove_reference_t<decltype(std::declval<C>().front())>>;
};

template <class C>
    requires detail::is_stack<C> and detail::is_queue<C>
struct try_pop_result<C> {
    static_assert(is_always_false<C>, "Ambiguous instantiation of `tmc::try_pop_result`");
};

template <class C>
    requires
    (detail::is_stack<C> or detail::is_queue<C>) and
    (detail::is_stack<C> != detail::is_queue<C>)
using try_pop_result_t = try_pop_result<C>::type;

// Pop value from a queue or a stack as an optional,
// returns nullopt when there is nothing to pop, e.g.
//
//    > while (const auto value = tmc::try_pop(queue)) { /* process value */ }
//
// In particular, this can be very convenient when ingesting a queue values that are nullable themselves:
//
//    > while (const auto value = tmc::try_pop(queue).value_or({})) { /* process value */ } 
//
template <class C>
    requires
    (detail::is_stack<C> or detail::is_queue<C>) and
    (detail::is_stack<C> != detail::is_queue<C>)
constexpr try_pop_result_t<C> try_pop(C& container) {
    using result_type = try_pop_result_t<C>;
    
    if (container.empty()) return result_type{};
    
    if constexpr (detail::is_stack<C>) {
        auto result = result_type{ std::move(container.top()) };
        
        container.pop();
        
        return result;
    }
    else {
        auto result = result_type{ std::move(container.front()) };
        
        container.pop();
        
        return result;
    }
}

} // namespace tmc
