# Copyright (c) 2024 German Aerospace Center (DLR)
# All rights reserved.
#
# This file is part of the STM32H753 sandbox.
#
# Authors:
# - 2024, Jan-Gerd Mess (DLR RY-AVS)
# - 2024, Pawel Buczek (HAW Hamburg)


include ../makefile.default.mk

PROGRAM_NAME = sandbox-breadboard

build: version
	@lbuild -p ../../gen/$(PROGRAM_NAME) build
	@scons -j4 -C .. install target=bb program_name=$(PROGRAM_NAME) 

program: build
	@scons -C .. program target=bb program_name=$(PROGRAM_NAME)

debug: build
	@scons -C .. debug target=bb program_name=$(PROGRAM_NAME)