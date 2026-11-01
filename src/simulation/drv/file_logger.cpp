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

namespace sandbox
{
namespace hal
{

FileLogger::FileLogger(const char* fileName) : mOutStream(fileName, std::ofstream::out)
{
}

void
FileLogger::log(const char* str)
{
    mOutStream << str;
}

void
FileLogger::log(int32_t i)
{
    mOutStream << i;
}

void
FileLogger::log(uint32_t i)
{
    mOutStream << i;
}

void
FileLogger::flushLog()
{
    mOutStream.flush();
}

}  // namespace hal
}  // namespace sandbox
