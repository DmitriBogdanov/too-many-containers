// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>  // ptrdiff_t
#include <iterator> // output_iterator_tag
#include <memory>   // addressof()
#include <utility>  // forward()

#include <tmc/concept/has_emplace_front.hpp>
#include <tmc/iterator/emplace_args.hpp>
#include <tmc/requirement/has_nothrow_emplace_front.hpp>

namespace tmc {

// `std::front_insert_iterator` / `std::front_inserter()` equivalent that uses emplacement instead of insertion.
// In some cases this allows iterator to work more efficiently or support more restrictive classes.
//
// Provided API is a perfect match of its inserting counterpart.
//
template <class Container>
struct front_emplace_iterator {
    using iterator_category = std::output_iterator_tag;
    using value_type        = void;
    using difference_type   = std::ptrdiff_t;
    using pointer           = void;
    using reference         = void;
    using container_type    = Container;

protected:

    container_type* c;

public:
    explicit constexpr front_emplace_iterator(container_type& c) noexcept : c(std::addressof(c)) {}

    constexpr front_emplace_iterator& operator* (   ) noexcept { return *this; }
    constexpr front_emplace_iterator& operator++(   ) noexcept { return *this; }
    constexpr front_emplace_iterator& operator++(int) noexcept { return *this; }

    // Regular single-argument emplacement
    template <class Arg>
        requires has_emplace_front<container_type, Arg>
    constexpr front_emplace_iterator& operator=(Arg&& arg)
        noexcept(has_nothrow_emplace_front<container_type, Arg>)
    {
        this->c->emplace_front(std::forward<Arg>(arg));
        
        return *this;
    }

    // Multi-argument emplacement with `tmc::emplace_args<>`
    template <class... Args>
        requires has_emplace_front<container_type, Args...>
    constexpr front_emplace_iterator& operator=(emplace_args<Args...>&& packed_args)
        noexcept(has_nothrow_emplace_front<container_type, Args...>)
    {
        tmc::apply(
            [&](auto&&... args) { this->c->emplace_front(std::forward<decltype(args)>(args)...); },
            std::move(packed_args.value)
        );
        
        return *this;
    }

    template <class... Args>
        requires has_emplace_front<container_type, Args...>
    constexpr front_emplace_iterator& operator=(emplace_args<Args...>& packed_args)
        noexcept(has_nothrow_emplace_front<container_type, Args...>)
    {
        tmc::apply([&](auto&&... args) {
            this->c->emplace_front(std::forward<decltype(args)>(args)...); },
            packed_args.value
        );
        
        return *this;
    }

    template <class... Args>
        requires has_emplace_front<container_type, Args...>
    constexpr front_emplace_iterator& operator=(const emplace_args<Args...>& packed_args)
        noexcept(has_nothrow_emplace_front<container_type, Args...>)
    {
        tmc::apply(
            [&](auto&&... args) { this->c->emplace_front(std::forward<decltype(args)>(args)...); },
            packed_args.value
        );
        
        return *this;
    }
};

template <class Container>
TMC_NO_DISCARD constexpr auto front_emplacer(Container& c) noexcept {
    return front_emplace_iterator<Container>{ c };
}

} // namespace tmc
