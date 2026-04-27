// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <exception> // exception
#include <format>    // format_string<>

#include <tmc/utility/nothrow_format_buffer.hpp>
#include <tmc/utility/source_location_capture.hpp>

namespace tmc {

// Base class for custom runtime exceptions, automatically captures `std::source_location`,
// and supports <format> in its constructor. Uses a fixed-size buffer of `capacity` to format
// in allocation-free manner (since we don't want exceptions to be thrown during construction).
//
template <std::size_t capacity = 512>
class formattable_exception : std::exception {
    tmc::nothrow_format_buffer<capacity> buffer{};

public:

    template <class... Args>
    formattable_exception(
        source_location_capture<std::format_string<Args...>> ctx, 
        Args&&...                                            args
    ) noexcept {
        this->buffer.try_format(ctx.fmt, std::forward<Args>(args)...);
    }

    virtual const char* what() const noexcept { return this->buffer.c_str(); }
};
    
} // namespace tmc
