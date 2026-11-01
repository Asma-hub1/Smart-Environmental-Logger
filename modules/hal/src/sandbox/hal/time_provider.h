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

#ifndef SANDBOX_HAL_TIME_PROVIDER_H_
#define SANDBOX_HAL_TIME_PROVIDER_H_

#include <inttypes.h>

namespace sandbox
{
namespace hal
{

class TimeProvider
{
public:
    virtual uint32_t
    getTimeStamp() const = 0;

    virtual ~TimeProvider() = default;
};

}  // namespace hal
}  // namespace sandbox

#endif /* SANDBOX_HAL_TIME_PROVIDER_H_ */
