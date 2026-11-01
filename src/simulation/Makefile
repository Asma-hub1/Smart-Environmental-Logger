# Copyright (c) 2024 German Aerospace Center (DLR)
# All rights reserved.
#
# This file is part of the STM32H753 sandbox.
#
# Authors:
# - 2024, Jan-Gerd Mess (DLR RY-AVS)


include ../makefile.default.mk

PROGRAM_NAME = sandbox-sim

build: version
	@lbuild -p ../../gen/$(PROGRAM_NAME) build
	@scons -j4 -C .. install target=host program_name=$(PROGRAM_NAME)

run:
	@scons -j4 -C .. run target=host program_name=$(PROGRAM_NAME)