// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <array>       // array<>
#include <format>      // format_string<>, format_to_n()
#include <string_view> // string_view
#include <utility>     // forward()

#include <tmc/macro/no_discard.hpp>
#include <tmc/macro/try_catch.hpp>

namespace tmc {

// Static buffer for exception-free runtime formatting, useful for formatting error
// messages in restricted contexts e.g. exception constructors, panic handlers and etc.
//
// Possible formatter exception are swallowed. Any text lost due to exceptions /
// running out of buffer will be replaced with diagnostic messages, e.g.:
//
//    "Assertion ... failed at [format_exception] with conte[buffer_exhausted]"
//
template <std::size_t capacity = 512>
class nothrow_format_buffer {
    constexpr static std::string_view format_exception_message = "[format_exception]";
    constexpr static std::string_view buffer_exhausted_message = "[buffer_exhausted]";

    constexpr static std::size_t format_capacity = capacity;
    constexpr static std::size_t string_capacity = format_capacity + buffer_exhausted_message.size();
    constexpr static std::size_t buffer_capacity = string_capacity + 1; // + 1 ensures null-terminator

    std::array<char, buffer_capacity> buffer = {};

    const char* beg = buffer.data();
    const char* end = buffer.data() + format_capacity;

public:
    
    template <class... Args>
    void try_format(std::format_string<Args...> fmt, Args&&... args) noexcept {
        const auto fmt_end = this->buffer.data() + format_capacity;
        const auto str_end = this->buffer.data() + string_capacity;
        
        TMC_TRY {
            this->beg = std::format_to_n(this->beg, fmt_end - this->beg, fmt, std::forward<Args>(args)...);
        } TMC_CATCH(...) {
            this->beg = std::format_to_n(this->beg, fmt_end - this->beg, "{}", this->format_exception_message);
        }
        
        if (this->beg == this->end)
            std::format_to_n(this->beg, str_end - this->beg, "{}", this->buffer_exhausted_message);
        
        // `std::format_to_n()` can only throw due to propagating iterator / formatter exceptions.
        // In case desired formatting fails, we can format a diagnostic message instead with noexcept
        // pointers as iterators & noexcept string literal as an argument, thus no exception will escape. 
    }
    
    TMC_NO_DISCARD
    const char* c_str() const noexcept {
        return this->buffer.data();
    }
    
};

} // namespace tmc
