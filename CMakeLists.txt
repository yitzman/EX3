cmake_minimum_required(VERSION 3.15)
project(EX3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(EX3
        Command.cpp
        Command.h
        main.cpp
        openServerCommand.cpp
        openServerCommand.h)
