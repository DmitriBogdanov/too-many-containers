// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef TMC_DISABLE_NO_DISCARD
    #define TMC_NO_DISCARD
#else
    #define TMC_NO_DISCARD [[nodiscard]]
#endif