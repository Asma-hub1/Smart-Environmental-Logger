/*
 * Copyright (c) 2023, German Aerospace Center (DLR)
 * All rights reserved.
 *
 *  This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2023, Jan-Gerd Mess (DLR RY-AVS)
 */

#include "../init.h"
#include "../support.h"

#include <modm/debug/logger.hpp>

#include <outpost/rtos.h>
#include <outpost/rtos/thread.h>

namespace sandbox
{
extern common::Version version;
}

int
main()
{
    // initialization procedure
    modm::log::info << "Hello World from OBC" << modm::endl;
    sandbox::printVersion(sandbox::version);
    modm::log::info << "- Initialize" << modm::endl;
    systemInit();
    modm::log::info << "- Start-Up" << modm::endl;
    startup();
    modm::log::info << "- Done" << modm::endl;

    while (true)
    {
        outpost::rtos::Thread::sleep(outpost::time::Duration::myriad());
    }

    return 0;
}
