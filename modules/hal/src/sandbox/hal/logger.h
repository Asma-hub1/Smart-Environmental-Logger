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
 * - 2024, Paweł Buczek (HAW Hamburg)
 *
 */

#ifndef SANDBOX_HAL_LOGGER_H_
#define SANDBOX_HAL_LOGGER_H_

#include <inttypes.h>

namespace sandbox
{
namespace hal
{

class Logger
{
public:
    Logger() = default;
    virtual ~Logger() = default;

    virtual void
    log(const char* str) = 0;

    virtual void
    log(int32_t i) = 0;

    virtual void
    log(uint32_t i) = 0;

    virtual void
    flushLog() = 0;
};

}  // namespace hal
}  // namespace sandbox

#endif /* SANDBOX_HAL_LOGGER_H_ */
