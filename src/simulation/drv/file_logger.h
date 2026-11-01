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
 * - 2024, Jan-Gerd Mess (DLR-RY-AVS)
 *
 */

#ifndef SANDBOX_SIMULATION_DRV_FILE_LOGGER_H_
#define SANDBOX_SIMULATION_DRV_FILE_LOGGER_H_

#include <sandbox/hal/logger.h>

#include <fstream>

namespace sandbox
{
namespace hal
{

class FileLogger : public Logger
{
public:
    FileLogger(const char* filename);

    ~FileLogger() = default;

    virtual void
    log(const char* str);

    void
    log(int32_t i) override;

    virtual void
    log(uint32_t i) override;

    virtual void
    flushLog() override;

private:
    std::ofstream mOutStream;
};

}  // namespace hal
}  // namespace sandbox

#endif /* SANDBOX_SIMULATION_DRV_FILE_LOGGER_H_ */