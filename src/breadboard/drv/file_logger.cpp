/*
 * Copyright (c) 2024
 * German Aerospace Center (DLR) and
 * HAW Hamburg
 *
 * All rights reserved.
 *
 * This file is part of the STM32H753 sandbox.
 *
 * Authors:
 * - 2024 Paweł Buczek (HAW Hamburg)
 *
 *
 */

#include "file_logger.h"

#include <modm/debug.hpp>

namespace sandbox
{
namespace hal
{

FileLogger::FileLogger()
{
}

void
FileLogger::log(const char* str)
{
    modm::log::info << str;
}

void
FileLogger::log(int32_t i)
{
    modm::log::info << i;
}

void
FileLogger::log(uint32_t i)
{
    modm::log::info << i;
}

void
FileLogger::flushLog()
{
}

}  // namespace hal
}  // namespace sandbox
