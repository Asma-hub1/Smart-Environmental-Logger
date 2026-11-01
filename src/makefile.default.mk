# Copyright (c) 2024 German Aerospace Center (DLR)
# All rights reserved.
#
# This file is part of the STM32H753 sandbox.
#
# Authors:
# - 2024, Jan-Gerd Mess (DLR RY-AVS)

ROOTPATH ?= ../..

VERSION_TOOL ?= $(ROOTPATH)/tools/version

FIRMWARE_VERSION ?= $(shell cat $(ROOTPATH)/latest_release.txt)-dev

version:
	@python3 $(VERSION_TOOL)/version_branding.py -r $(ROOTPATH) --version $(FIRMWARE_VERSION)