#
# Hello Word Demo
#
# Copyright (C) 2019-2020, Hensoldt Cyber GmbH
#

cmake_minimum_required(VERSION 3.7.2)


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
