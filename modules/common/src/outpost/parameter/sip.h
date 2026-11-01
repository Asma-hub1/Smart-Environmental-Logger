/*
 * Copyright (c) 2021-2023, German Aerospace Center (DLR)
 *
 * This file is part of the development version of the Simple Interface
 * Protocol.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  Authors:
 *  - 2021, Norbert Toth (DLR RY-AVS)
 *  - 2023, Felix Passenberg (DLR RY-AVS)
 */

#ifndef OUTPOST_SIP_PARAMETER_SIP_H_
#define OUTPOST_SIP_PARAMETER_SIP_H_

#include <outpost/sip/constants.h>

#include <limits>
#include <stddef.h>
#include <stdint.h>

#include <type_traits>

namespace outpost
{
namespace sip
{
namespace parameter
{
static constexpr uint16_t maxPayloadLength = 256;

static constexpr size_t maxPacketLength = maxPayloadLength + constants::packetOverhead;
static_assert(std::numeric_limits<decltype(maxPayloadLength)>::max() - constants::structureInLength
                      > maxPacketLength,
              "The length field must contain Payload and Header/CRC length");

enum class defaultRequestType : uint8_t
{
    linkTest = 0x01,
    hkRequest = 0x02
    /* 0x02-0x0f reserved */
    /* ======================================= */
    /* 0x10-0x7f application specific requests */
};

enum class defaultResponseType : uint8_t
{
    framingErorr = 0x80,
    errorAck = 0x81,
    successAck = 0x82,
    hkResponse = 0x83
    /* 0x84-0x8f reserved */
    /* ======================================= */
    /* 0x90-0xff application specific response */
};

}  // namespace parameter
}  // namespace sip
}  // namespace outpost

#endif /* OUTPOST_SIP_PARAMETER_SIP_H_ */
