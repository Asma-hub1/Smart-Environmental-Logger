/*
 * Copyright (c) 2024, German Aerospace Center (DLR)
 * All rights reserved.
 *
 *  This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2024, Jan-Gerd Mess (DLR RY-AVS)
 */

#ifndef STM32H753_COMMON_THREAD_PRIORITIES_H_
#define STM32H753_COMMON_THREAD_PRIORITIES_H_

namespace sandbox
{
namespace common
{
namespace thread_priority
{
static constexpr uint8_t epsHousekeepingThread = 10;
static constexpr uint8_t comReceiverThread = 11;
}  // namespace thread_priority
}  // namespace common
}  // namespace sandbox

#endif