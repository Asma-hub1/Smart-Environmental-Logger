/*
 * Copyright (c) 2023, German Aerospace Center (DLR)
 * All rights reserved.
 *
 *  This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2024, Jan-Gerd Mess (DLR RY-AVS)
 */

#include "support.h"

#include <modm/debug/logger.hpp>

void
sandbox::printVersion(const sandbox::common::Version& version)
{
    modm::log::info << "Version " << version.release << "." << version.major << "."
                    << version.minor;

    if (version.type == sandbox::common::VersionType::development)
    {
        modm::log::info << "-dev" << modm::endl;
    }
    else
    {
        modm::log::info << modm::endl;
    }

    modm::log::info << "Revision " << version.vcsRevision.data()
                    << (version.vcsModified ? "-M" : " ") << modm::endl;
}
