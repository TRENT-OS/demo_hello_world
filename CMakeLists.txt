#
# Demo Hello Word
#
# Copyright (C) 2019-2020, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)


#-------------------------------------------------------------------------------
project(tests_hello_world C)

DeclareCAmkESComponent(
    hello_world_app
    INCLUDES
        components/hello_world_app/
    SOURCES
        components/hello_world_app/src/main.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        # no libs needed
)

DeclareCAmkESComponent(
    hello_world_sender
    INCLUDES
        components/hello_world_sender/
    SOURCES
        components/hello_world_sender/src/main.c
    C_FLAGS
        -Wall
        -Werror
    LIBS
        os_core_api
        # no libs needed
)

CAmkESAddTemplatesPath(connector)

DeclareCAmkESConnector(
    trentos_thread
    FROM
    trentos_thread-to-template.c
    TO
    trentos_thread-to-template.c
    TO_HEADER
    trentos_thread-to-template.h
)

DeclareAndCreateCamkESSystem(demo_hello_world.camkes)
GenerateSimulateScript()
