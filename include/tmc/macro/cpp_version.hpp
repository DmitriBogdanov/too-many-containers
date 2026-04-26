// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#if defined(_MSC_VER) and defined(_MSVC_LANG)
    #define TMC_CPP_VERSION _MSVC_LANG
#else
    #define TMC_CPP_VERSION __cplusplus
#endif

#define TMC_CPP_20 202002L
#define TMC_CPP_23 202302L
