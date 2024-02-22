#
# Demo Hello Word
#
# Copyright (C) 2019-2024, HENSOLDT Cyber GmbH
# 
# SPDX-License-Identifier: GPL-2.0-or-later
#
# For commercial licensing, contact: info.cyber@hensoldt.net
#

cmake_minimum_required(VERSION 3.7.2)

find_package("os-sdk" REQUIRED)
os_sdk_set_defaults()
os_sdk_setup()

#-------------------------------------------------------------------------------
project(tests_hello_world C)

DeclareCAmkESComponent(
    hello_world_app
    INCLUDES
        # no include paths needed
    SOURCES
        components/hello_world_app/src/main.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        # no libs needed
)

os_sdk_create_CAmkES_system(demo_hello_world.camkes)
