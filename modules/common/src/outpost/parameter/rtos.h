/*
 * Copyright (c) 2023, German Aerospace Center (DLR)
 *
 * This file is part of the development version of OUTPOST
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  Authors:
 *  - 2023, Hannah Kirstein (DLR RY-AVS)
 */

#ifndef OUTPOST_RTOS_PARAMETER_RTOS_H_
#define OUTPOST_RTOS_PARAMETER_RTOS_H_

#include <limits>
#include <stddef.h>
#include <stdint.h>

#include <type_traits>

namespace outpost
{
namespace rtos
{
/**
 * Number of CPUs.
 */
static constexpr uint8_t cpuCount = 2;

/**
 * CPU Mask used for thread affinity assignment.
 * Bit count of CpuMask must be at least cpuCount.
 */
typedef uint8_t CpuMask;
static_assert(sizeof(CpuMask) * 8 >= cpuCount, "CpuMask too small for cpuCount!");

/**
 * Used for affinity assignment to inherit affinity of calling thread.
 */
static constexpr CpuMask inheritFromCaller = 0;

/**
 * Used for affinity assignment to specify the index of a CPU.
 */
enum class CpuAffinity : uint8_t;
static_assert(std::numeric_limits<std::underlying_type<CpuAffinity>::type>::max() >= cpuCount,
              "CpuAffinity type cannot handle number of CPUs requested");

/**
 * operator to use CPU affinities as flags to create a CPU mask.
 */
constexpr inline CpuMask
operator|(CpuAffinity a, CpuAffinity b)
{
    return (1 << (static_cast<CpuMask>(a))) | (1 << (static_cast<CpuMask>(b)));
}

/**
 * Operator to add a CPU affinity to a CPU mask.
 */
constexpr inline CpuMask
operator|(CpuMask a, CpuAffinity b)
{
    return a | (1 << (static_cast<CpuMask>(b)));
}

/**
 * Operator to add a CPU affinity to a CPU mask.
 */
constexpr inline CpuMask
operator|(CpuAffinity a, CpuMask b)
{
    return (1 << (static_cast<CpuMask>(a))) | b;
}

/**
 * Convert a CPU affinity to a CPU mask.
 */
constexpr inline CpuMask
toCpuMask(CpuAffinity a)
{
    return 1 << static_cast<CpuMask>(a);
}

}  // namespace rtos
}  // namespace outpost

#endif /* OUTPOST_RTOS_PARAMETER_RTOS_H_ */
