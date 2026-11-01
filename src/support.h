/*
 * Copyright (c) 2023, German Aerospace Center (DLR)
 * All rights reserved.
 *
 *  This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2024, Jan-Gerd Mess (DLR RY-AVS)
 */

#ifndef STM32H753_SUPPORT_H_
#define STM32H753_SUPPORT_H_

#include <sandbox/common/version.h>

namespace sandbox
{

void
printVersion(const sandbox::common::Version& version);

}

#endif