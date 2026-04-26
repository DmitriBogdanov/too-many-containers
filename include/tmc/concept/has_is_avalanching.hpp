// SPDX-FileCopyrightText: Copyright (c) 2026 - present, Dmitri Bogdanov
// SPDX-FileCopyrightText: https://github.com/DmitriBogdanov/too-many-containers
//
// SPDX-License-Identifier: MIT

#pragma once

namespace tmc {

template <class T>
concept has_is_avalanching = requires {
    typename T::is_avalanching;
    // this annotation is used to signify hashes with avalanching effect
    // (any change in the input bits has a 50/50 chance to flip all bits of the hash)
};

} // namespace tmc
