/*
 * Copyright (c) 2015, 2017-2018, 2024 German Aerospace Center (DLR)
 * All rights reserved.
 *
 * This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2015, 2017-2018, Fabian Greif (DLR RY-AVS)
 * - 2024, Jan-Gerd Mess (DLR RY-AVS)
 */

#ifndef STM32H753_VERSION_H
#define STM32H753_VERSION_H

#include <stdint.h>

#include <array>

namespace sandbox
{
namespace common
{
enum class VersionType
{
    release = 0,
    development = 1
};

/**
 * Version information for the Flight Software build.
 */
struct Version
{
    uint8_t release;
    uint8_t major;
    uint8_t minor;

    VersionType type;

    std::array<const char, 13> vcsRevision;
    bool vcsModified;
};

}  // namespace common
}  // namespace sandbox

#endif
