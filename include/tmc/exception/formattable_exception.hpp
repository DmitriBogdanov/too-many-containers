// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <array>     // array<>
#include <exception> // exception
#include <format>    // format_to_n()

#include <tmc/macro/try_catch.hpp>
#include <tmc/utility/source_location_capture.hpp>

namespace tmc {

// Base class for custom runtime exceptions, automatically captures `std::source_location`,
// and supports <format> in its constructor. Uses a fixed-size buffer of `capacity` to format
// in allocation-free manner (since we don't want exceptions to be thrown during construction).
//
// When inheriting adjust capacity to suit the expected message. Note that strictly speaking
// we still can't guarantee exception-free formatting due to possible throws from `std::formatter`,
// but in practice its quite rare to throw from the formatter unless some state is already corrupted,
// in case that still happens we will simply swallow the exception and format what we could.
//
template <std::size_t capacity = 256>
class formattable_exception : std::exception {
    constexpr static std::size_t format_capacity = capacity;
    constexpr static std::size_t buffer_capacity = format_capacity + 1;

    std::array<char, buffer_capacity> buffer{};
    
    // buffer is larger by 1 => there is always some place left for the null terminator
    //
    // buffer is null-initialized => values after the formatted range will always contain a null terminator

public:

    template <class... Args>
    formattable_exception(
        source_location_capture<std::format_string<Args...>> ctx, 
        Args&&...                                            args
    ) noexcept {
        auto beg = this->buffer.data();
        auto end = beg + format_capacity;
        
        TMC_TRY {
            beg = std::format_to_n(beg, end - beg, "[{}:{}]: ", ctx.loc.file_name(), ctx.loc.line()).out;
            beg = std::format_to_n(beg, end - beg, ctx.fmt, std::forward<Args>(args)...).out;
        }
        TMC_CATCH(...) {}
    }

    virtual const char* what() const noexcept { return this->buffer.data(); }
};
    
} // namespace tmc
