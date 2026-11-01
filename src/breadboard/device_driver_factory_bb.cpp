/*
 * Copyright (c) 2024, German Aerospace Center (DLR)
 * All rights reserved.
 *
 *  This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2024, Jan-Gerd Mess (DLR RY-AVS)
 */

#include "../device_driver_factory.h"
#include "drv/file_logger.h"

#include <modm/board.hpp>

#include <outpost/hal/arch/modm/clock.h>

namespace sandbox
{
namespace hal
{

static outpost::modm::Clock clock;

outpost::time::Clock&
DeviceDriverFactory::getClock()
{
    return clock;
}

Logger&
DeviceDriverFactory::getObcLogger()
{
    static FileLogger fileLogger;
    return fileLogger;
}

Logger&
DeviceDriverFactory::getAdcLogger()
{
    static FileLogger fileLogger;
    return fileLogger;
}

}  // namespace hal
}  // namespace sandbox