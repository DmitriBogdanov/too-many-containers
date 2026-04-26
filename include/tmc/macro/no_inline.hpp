// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef TMC_DISABLE_NO_INLINE
    #define TMC_NO_INLINE
#elif defined(_MSC_VER)
    #define TMC_NO_INLINE __declspec((noinline))
#elif defined(__clang__) or defined(__GNUC__)
    #define TMC_NO_INLINE __attribute__((noinline))
#else
    #define TMC_NO_INLINE
#endif
