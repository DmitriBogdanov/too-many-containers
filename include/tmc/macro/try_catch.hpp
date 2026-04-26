// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

#ifdef TMC_DISABLE_EXCEPTIONS
    #include <cstdlib> // std::abort()
#endif

#ifdef TMC_DISABLE_EXCEPTIONS
    #define TMC_TRY      if constexpr (true)
    #define TMC_CATCH(x) if constexpr (false)
    #define TMC_RETHROW
    #define TMC_THROW(x) std::abort()
#else
    #define TMC_TRY      try
    #define TMC_CATCH(x) catch (x)
    #define TMC_RETHROW  throw
    #define TMC_THROW(x) throw ((x))
#endif
