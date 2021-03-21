#
# Demo Hello Word
#
# Copyright (C) 2019-2020, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)


#-------------------------------------------------------------------------------
project(tests_hello_world CXX)

DeclareCAmkESComponent(
    hello_world_app
    INCLUDES
        # no include paths needed
    SOURCES
        components/hello_world_app/src/main.cpp
    C_FLAGS
        -Wall
        -Werror
    CXX_FLAGS
        -Wall
        -Werror
        -fno-exceptions
        -fno-rtti
    LIBS
        os_core_api
        etl
)

DeclareAndCreateCamkESSystem(demo_hello_world.camkes)
GenerateSimulateScript()

project(etl CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    INTERFACE
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        etl
)
