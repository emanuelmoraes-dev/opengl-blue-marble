cmake_minimum_required(VERSION 3.21)
PROJECT(opengl_blue_marble CXX)

add_executable(BlueMarble)

target_sources(
    BlueMarble
    PRIVATE
        src/main.cc
        src/info.cc
        src/fs.cc
        src/shaders.cc
        src/textures.cc
        src/fly_camera.cc
        src/delta.cc
        src/scenes.cc
        src/scenes/quad.cc
        src/scenes/sphere.cc
)

target_include_directories(
    BlueMarble
    PRIVATE
        src/headers
)

target_compile_features(
    BlueMarble
    PUBLIC
        cxx_std_17
)

include(cmake/base.cmake)
include(cmake/os.cmake)
include(cmake/debug.cmake)
include(cmake/release.cmake)
