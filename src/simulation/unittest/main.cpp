/*
 * Copyright (c) 2013-2015, 2017-2018, German Aerospace Center (DLR)
 * All rights reserved.
 *
 * This file is part of the development version of OUTPOST.
 *
 * May contain parts that are subject to export control under
 * the terms of AL Nr.: 9D005 (EG Nr. 428/2009 Dual Use) for
 * export to countries outside the EU.
 *
 * Authors:
 * - 2013-2015, 2017-2018, Fabian Greif (DLR RY-AVS)
 */

#include <testUtils/configurable_event_listener.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

int
main(int argc, char** argv)
{
    // InitGoogleMock initializes Google test, too.
    ::testing::InitGoogleMock(&argc, argv);

    // Using the default listener from testUtils for customized gtest output
    testUtils::registerConfigurableEventListener();

    return RUN_ALL_TESTS();
}
