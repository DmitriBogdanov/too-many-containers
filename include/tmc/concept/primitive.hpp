// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Constraints for (mostly) primitive types

#include <concepts>    // std::constructible_from<>
#include <type_traits> // std::is_enum_v<>, is_is_rvalue_reference_v<>, ...


namespace tmc::req {

template <class T>
concept reference = std::is_reference_v<T>;
    
template <class T>
concept rvalue_reference = std::is_rvalue_reference_v<T>;

template <class T>
concept lvalue_reference = std::is_lvalue_reference_v<T>;

template <class T>
concept const_reference = std::is_reference_v<T> and std::is_const_v<std::remove_reference_t<T>>;

template <class T>
concept cv_unqualified = not std::is_const_v<T> and not std::is_volatile_v<T>;

template <class T>
concept array = std::is_array_v<T>;

template <class T>
concept non_array = not std::is_array_v<T>;

template <class T>
concept enumeration = std::is_enum_v<T>;

template <class T>
concept arithmetic = std::is_arithmetic_v<T>;

template <class T>
concept boolean_testable = std::constructible_from<bool, T>;

// Note: satisfied when 'T' is explicitly convertible to 'bool' => can be
//       used in boolean test expression (e.g. `if (cond)`), this is a weaker
//       requirement than seemingly more intuitive `std::convertible_to<bool>`

} // namespace tmc::req
