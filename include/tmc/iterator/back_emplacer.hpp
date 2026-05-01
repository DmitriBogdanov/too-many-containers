// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>  // ptrdiff_t
#include <iterator> // output_iterator_tag
#include <memory>   // addressof()
#include <utility>  // forward()

#include <tmc/concept/has_emplace_back.hpp>
#include <tmc/iterator/emplace_args.hpp>
#include <tmc/requirement/has_nothrow_emplace_back.hpp>

namespace tmc {

// `std::back_insert_iterator` / `std::back_inserter()` equivalent that uses emplacement instead of insertion.
// In some cases this allows iterator to work more efficiently or support more restrictive classes.
//
// Provided API is a perfect match of its inserting counterpart.
//
template <class Container>
struct back_emplace_iterator {
    using iterator_category = std::output_iterator_tag;
    using value_type        = void;
    using difference_type   = std::ptrdiff_t;
    using pointer           = void;
    using reference         = void;
    using container_type    = Container;

protected:

    container_type* c;

public:
    explicit constexpr back_emplace_iterator(container_type& c) noexcept : c(std::addressof(c)) {}

    constexpr back_emplace_iterator& operator* (   ) noexcept { return *this; }
    constexpr back_emplace_iterator& operator++(   ) noexcept { return *this; }
    constexpr back_emplace_iterator& operator++(int) noexcept { return *this; }

    // Regular single-argument emplacement
    template <class Arg>
        requires has_emplace_back<container_type, Arg>
    constexpr back_emplace_iterator& operator=(Arg&& arg)
        noexcept(has_nothrow_emplace_back<container_type, Arg>)
    {
        this->c->emplace_back(std::forward<Arg>(arg));
    }

    // Multi-argument emplacement with `tmc::emplace_args<>`
    template <class... Args>
        requires has_emplace_back<container_type, Args...>
    constexpr back_emplace_iterator& operator=(emplace_args<Args...>&& packed_args)
        noexcept(has_nothrow_emplace_back<container_type, Args...>)
    {
        tmc::apply(
            [&](auto&&... args) { this->c->emplace_back(std::forward<decltype(args)>(args)...); },
            std::move(packed_args)
        );
    }

    template <class... Args>
        requires has_emplace_back<container_type, Args...>
    constexpr back_emplace_iterator& operator=(emplace_args<Args...>& packed_args)
        noexcept(has_nothrow_emplace_back<container_type, Args...>)
    {
        tmc::apply([&](auto&&... args) {
            this->c->emplace_back(std::forward<decltype(args)>(args)...); },
            packed_args
        );
    }

    template <class... Args>
        requires has_emplace_back<container_type, Args...>
    constexpr back_emplace_iterator& operator=(const emplace_args<Args...>& packed_args)
        noexcept(has_nothrow_emplace_back<container_type, Args...>)
    {
        tmc::apply(
            [&](auto&&... args) { this->c->emplace_back(std::forward<decltype(args)>(args)...); },
            packed_args
        );
    }
};

template <class Container>
TMC_NO_DISCARD constexpr auto back_emplacer(Container& c) noexcept {
    return back_emplace_iterator<Container>{ c };
}

} // namespace tmc
