#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2016-2024, German Aerospace Center (DLR)
# All rights reserved.
#
# This file is part of the STM32H753 sandbox.
#
# Authors:
# - 2016-2018, Fabian Greif (DLR RY-AVS)

import re
import os
import sys
import time
import argparse
import subprocess

scriptpath = os.path.dirname(os.path.realpath(__file__))

VERSION_TYPE_MAPPING = {
    None: "VersionType::release",
    "dev": "VersionType::development"
}

arg = argparse.ArgumentParser(description='Version information generator')
arg.add_argument('-r', '--root', dest='rootpath', required=True, help='Path to the project root folder.')
arg.add_argument('--version', dest='version', required=True,
                 help='Software version information (in the format "Release.Major.Minor-Type").')
arg.add_argument('-t', '--template', dest='template', default=os.path.join(scriptpath, 'version.cpp.in'),
                 help='Template from which the target file will be generated.')
arg.add_argument('-o', '--output', dest='output', default='version.cpp', help='Target file.')
arg.add_argument('-p', '--patchfile', dest='patchfile', default='version.diff',
                 help='Patch file containing the current local changes in case of a modified revision.')
arg.add_argument('-v', '--info', dest='infofile', default='version.info',
                 help='Human readable version information.')

args = arg.parse_args()

version_identifier = args.version
m = re.match('^\s*(\d+)\.(\d+)\.(\d+)(|-(.*))$', version_identifier)

version_release = m.group(1)
version_major = m.group(2)
version_minor = m.group(3)
version_type = m.group(5)

vcs_type = None
try:
    revision_output = subprocess.Popen(["git", "rev-parse", "HEAD"],
                                        stdout=subprocess.PIPE).communicate()[0]

    revision_output = revision_output.decode("UTF-8").strip()
    if len(revision_output) != 40:
        raise Exception("Error while reading the Git revision: '{}'".format(revision_output))
    revision = revision_output[:7]

    modified_output = subprocess.Popen(["git", "status", "--porcelain", "--untracked-files=no"],
                                        stdout=subprocess.PIPE).communicate()[0]
    revision_modified = "true" if len(modified_output) > 0 else "false"
    vcs_type = "git"
except:
    revision = "-"
    revision_modified = "false"
    vcs_type = "no"


template_data = open(args.template).read()
with open(args.output, 'w') as branding_file:
    branding_file.write(template_data.format(release=version_release,
                                             major=version_major,
                                             minor=version_minor,
                                             version_type=VERSION_TYPE_MAPPING[version_type],
                                             revision=revision,
                                             revision_modified_flag=revision_modified))

if vcs_type in ["no"]:
    with open(args.patchfile, 'w') as patchFile:
        patchFile.write("")
else:
    # Create a patch with the current changes in the repository
    patch = subprocess.Popen([vcs_type, "diff"],
                             stdout=subprocess.PIPE,
                             cwd=os.path.abspath(args.rootpath)).communicate()[0]
    with open(args.patchfile, 'w') as patchFile:
        patchFile.write(patch.decode('utf-8'))

with open(args.infofile, 'w') as branding_file:
    branding_file.write("""OBC Flight Software

Version: {version_string}
{vcs} revision: {revision}
{vcs} modified: {revision_modified_flag}
""".format(version_string=version_identifier,
           revision=revision,
           revision_modified_flag=revision_modified,
           vcs=vcs_type.capitalize()))
