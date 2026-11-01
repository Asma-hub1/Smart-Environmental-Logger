#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2016-2017, German Aerospace Center (DLR)
# All rights reserved.
#
# This file is part of the STM32H753 sandbox.
#
# Authors:
# - 2016-2017, Fabian Greif (DLR RY-AVS)

import re
import os
import sys

VERSION_TYPE_MAPPING = {
    None: 0,
    "": 0,
    "dev": 1
}

if __name__ == '__main__':
    version = sys.argv[1]
    if os.path.exists(version):
        version_string = open(version).read()
    else:
        version_string = version

    match = re.match("^(\d+)\.(\d+)\.(\d+)(|-(.*))$", version_string)
    if match:
        version_type = VERSION_TYPE_MAPPING[match.group(5)]
        identifier = int(match.group(1)) * 2 ** 24 + \
                     int(match.group(2)) * 2 ** 16 + \
                     int(match.group(3)) * 2 ** 8 + \
                     version_type
        print("0x{:08X}".format(identifier))
    else:
        print("Could not generate identifier from string '{}'".format(version_string))
        sys.exit(1)
