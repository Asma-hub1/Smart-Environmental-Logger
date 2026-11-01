# Copyright (c) 2024 German Aerospace Center (DLR)
# All rights reserved.
#
# This file is part of the STM32H753 sandbox.
#
# Authors:
# - 2024, Jan-Gerd Mess (DLR RY-AVS)

CLANG_FORMAT=clang-format

SOURCE_FILES = $(shell find . -type f -name '*.cpp*')
HEADER_FILES = $(shell find . -type f -name '*.h*')

format:
	@$(CLANG_FORMAT) -i $(SOURCE_FILES)
	@$(CLANG_FORMAT) -i $(HEADER_FILES)