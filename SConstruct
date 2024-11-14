#!/usr/bin/env python
import os
import sys

AddOption(
    '--prefix',
    dest='prefix',
    type='string',
    nargs=1,
    action='store',
    metavar='DIR',
    help='installation prefix',
)

AddOption(
    '--realsense-sdk',
    dest='realsense_sdk',
    type='string',
    nargs=1,
    action='store',
    metavar='DIR',
    help='realsense sdk directory',
)

env = SConscript("godot-cpp/SConstruct")
env.Append(PREFIX=GetOption('prefix'), REALSENSE_SDK=GetOption('realsense_sdk'), CXXFLAGS=["-fexceptions"], CPPPATH=["src/", "$REALSENSE_SDK/include"], LIBPATH='$REALSENSE_SDK/lib64', LIBS=['realsense2'])
sources = Glob("src/*.cpp")
library = env.SharedLibrary(
    "$PREFIX/bin/librealsense{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
    source=sources,
)

Default(library)
