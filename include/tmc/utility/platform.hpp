// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

// Content: Platform-specific macros & attributes


// TMC_NO_UNIQUE_ADDRESS

#ifdef _MSC_VER
#define TMC_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#define TMC_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

// TMC_ALWAYS_INLINE

#if defined(_MSC_VER) and not defined(__clang__)
#define TMC_ALWAYS_INLINE [[msvc::forceinline]] inline
#else
#define TMC_ALWAYS_INLINE inline __attribute__((always_inline))
#endif

// TMC_NO_INLINE

#ifdef _MSC_VER
#define TMC_NO_INLINE __declspec((noinline))
#elif defined(__clang__) or defined(__GNUC__)
#define TMC_NO_INLINE __attribute__((noinline))
#endif
