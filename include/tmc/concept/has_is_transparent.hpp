// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

namespace tmc {

template <class T>
concept has_is_transparent = requires {
    typename T::is_transparent;
    // this annotation is used to signify transparent hashes and comparators
};

} // namespace tmc
