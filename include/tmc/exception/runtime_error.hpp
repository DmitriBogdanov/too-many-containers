// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#include <tmc/exception/formattable_exception.hpp>

namespace tmc {

struct runtime_error : formattable_exception<> {
    using base = formattable_exception;

    using base::base;
};

} // namespace tmc
