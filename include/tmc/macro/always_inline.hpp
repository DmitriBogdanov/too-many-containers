// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef TMC_DISABLE_ALWAYS_INLINE
    #define TMC_ALWAYS_INLINE inline
#elif defined(_MSC_VER) and not defined(__clang__)
    #define TMC_ALWAYS_INLINE [[msvc::forceinline]] inline
#elif defined(__clang__) or defined(__GNUC__)
    #define TMC_ALWAYS_INLINE inline __attribute__((always_inline))
#else
    #define TMC_ALWAYS_INLINE inline
#endif
