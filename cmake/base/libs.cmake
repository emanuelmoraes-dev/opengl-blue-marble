target_include_directories(
    BlueMarble
    PRIVATE
        libs/glm
        libs/stb
)

target_link_libraries(
    BlueMarble
    PRIVATE
        base
)

if (WIN32)
    # windows

    target_include_directories(
        BlueMarble
        PRIVATE
            libs/glfw/include
            libs/glew/include
    )

    target_link_directories(
        BlueMarble
        PRIVATE
            libs/glfw/lib-vc2019
            libs/glew/lib/Release/x64
    )

    target_link_libraries(
        BlueMarble
        PRIVATE
            glfw3.lib
            glew32.lib
            opengl32.lib
    )
else()
    # linux

    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)

    target_link_libraries(
        BlueMarble
        PRIVATE
            GLEW::glew
            glfw
            OpenGL::OpenGL
    )
endif()
