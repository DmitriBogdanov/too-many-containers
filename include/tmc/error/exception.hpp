// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Exception type with <source_location> and <format> support

#include <array>  // std::array<>, std::size_t
#include <format> // std::format_to_n()

#include <tmc/error/source_location.hpp> // tmc::format_string_with_location<>


namespace tmc {

// Base class for custom runtime exceptions, automatically captures `std::source_location`,
// and supports <format> in constructor. Uses a fixed-size buffer of `capacity` to format
// in allocation-free manner (since we don't want exceptions to throw during construction).
//
// When inheriting adjust capacity to suit the expected message. Note that strictly speaking
// we still can't guarantee `noexcept` due to possible throws from `std::formatter`, but in
// practice its quite rare to throw from the formatter unless some state is already corrupted.
//
template <std::size_t capacity = 256>
class runtime_exception_base : std::exception {
    constexpr static std::size_t format_capacity = capacity;
    constexpr static std::size_t buffer_capacity = format_capacity + 1;
    // `buffer_capacity` larger by 1 => there is always some place left for the null terminator

    std::array<char, buffer_capacity> buffer{};
    // null initialization => values after the formatting range will always contain a null terminator

public:
    template <class... Args>
    runtime_exception_base(tmc::format_string_with_location<Args...> ctx, Args&&... args) {
        auto beg = this->buffer.data();
        auto end = beg + format_capacity;

        beg = std::format_to_n(beg, end - beg, "[{}:{}]: ", ctx.loc.file_name(), ctx.loc.line()).out;
        beg = std::format_to_n(beg, end - beg, ctx.fmt, std::forward<Args>(args)...).out;
    }

    virtual const char* what() const noexcept { return this->buffer.data(); }
};

// Exception types
class runtime_error : runtime_exception_base<> {
    using base = runtime_exception_base<>;

public:
    using base::base;
};

} // namespace tmc
