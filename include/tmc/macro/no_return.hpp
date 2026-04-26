// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef TMC_DISABLE_NO_RETURN
    #define TMC_NO_RETURN
#else
    #define TMC_NO_RETURN [[noreturn]]
#endif
