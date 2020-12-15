#
# Demo Hello Word
#
# Copyright (C) 2019-2020, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)

if (NOT OS_SDK_PATH)
    message(FATAL_ERROR "OS_SDK_PATH not set")
endif()
include("${OS_SDK_PATH}/CMakeLists.txt")
os_sdk_setup_build()


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

DeclareAndCreateCamkESSystem(demo_hello_world.camkes)
GenerateSimulateScript()
