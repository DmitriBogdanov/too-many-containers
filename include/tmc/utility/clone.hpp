// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <type_traits> // remove_cvref_t<>
#include <utility>     // forward()

#include <tmc/concept/is_explicitly_copyable.hpp>
#include <tmc/macro/no_discard.hpp>
#include <tmc/requirement/is_nothrow_copy_constructible.hpp>

namespace tmc {

// Deduce type & create explicit copy of the value
template <class T, class V = std::remove_cvref_t<T>>
    requires is_explicitly_copyable<V>
TMC_NO_DISCARD auto clone(T&& value)
    noexcept(is_nothrow_copy_constructible<V>)
{
    return V(std::forward<T>(value));
}

} // namespace tmc
