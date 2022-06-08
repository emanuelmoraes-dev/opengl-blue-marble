cmake_minimum_required(VERSION 3.21)
PROJECT(opengl_blue_marble CXX)

add_executable(BlueMarble)

target_sources(
    BlueMarble
    PRIVATE
        src/main.cc
)

target_compile_features(
    BlueMarble
    PUBLIC
        cxx_std_17
)

include(cmake/base.cmake)