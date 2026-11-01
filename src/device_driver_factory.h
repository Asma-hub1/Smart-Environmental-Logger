/*
 * Copyright (c) 2024, German Aerospace Center (DLR)
 * All rights reserved.
 *
 *  This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2024, Jan-Gerd Mess (DLR RY-AVS)
 */

#ifndef STM32H753_DEVICE_DRIVER_FACTORY_H_
#define STM32H753_DEVICE_DRIVER_FACTORY_H_

#include <sandbox/hal/logger.h>

#include <outpost/time/clock.h>

namespace sandbox
{
namespace hal
{

class DeviceDriverFactory
{
public:
    DeviceDriverFactory() = default;
    ~DeviceDriverFactory() = default;

    void
    init();

    outpost::time::Clock&
    getClock();

    Logger&
    getObcLogger();
    Logger&
    getAdcLogger();

};

}  // namespace hal
}  // namespace sandbox

#endif