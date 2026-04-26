// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef TMC_DISABLE_NO_UNIQUE_ADDRESS
    #define TMC_NO_UNIQUE_ADDRESS
#elif defined(_MSC_VER)
    #define TMC_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
    #define TMC_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif
