// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/concept/has_back.hpp>
#include <tmc/concept/has_empty.hpp>
#include <tmc/concept/has_pop.hpp>
#include <tmc/concept/has_top.hpp>
#include <tmc/concept/is_always_false.hpp>
#include <tmc/container/optional.hpp>
#include <tmc/macro/no_discard.hpp>

namespace tmc::detail {

template <class C> concept is_stack = has_empty<C> and has_pop<C> and not has_back<C> and     has_top<C>;
template <class C> concept is_queue = has_empty<C> and has_pop<C> and     has_back<C> and not has_top<C>;

} // namespace tmc::detail


namespace tmc {

template <class C>
    requires
    (detail::is_stack<C> or detail::is_queue<C>) and
    (detail::is_stack<C> != detail::is_queue<C>)
struct try_pop_result {
    using type = std::conditional_t<
        detail::is_stack<C>,
        optional<decltype(std::declval<C>().top ())>,
        optional<decltype(std::declval<C>().back())>
    >;
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
template <class C>
    requires
    (detail::is_stack<C> or detail::is_queue<C>) and
    (detail::is_stack<C> != detail::is_queue<C>)
TMC_NO_DISCARD try_pop_result_t<C> try_pop(C& container) {
    using result_type = try_pop_result_t<C>;
    
    if (container.empty()) return result_type{};
    
    if constexpr (detail::is_stack<C>) {
        auto result = result_type{ std::move(container.top()) };
        
        container.pop();
        
        return result;
    }
    else {
        auto result = result_type{ std::move(container.back()) };
        
        container.pop();
        
        return result;
    }
}

} // namespace tmc
