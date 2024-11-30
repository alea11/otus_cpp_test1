cmake_minimum_required(VERSION 3.12)

project(01.cmake_HW)

add_executable(hello_world
    hello_world.cpp
    ex.h
    ex.cpp
)

set_target_properties(hello_world PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)