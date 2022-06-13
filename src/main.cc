#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "errors.hh"
#include "window.hh"
#include "info.hh"
#include "scenes.hh"

int main() {
    int err = 0;

    err = glfwInit();
    if (err != GLFW_TRUE) {
        CERR(BME_GLFW_INIT, err);
        return BME_GLFW_INIT;
    }

    GLFWwindow* window = glfwCreateWindow(BMW_WIDTH, BMW_HEIGHT, BMW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        CERR(BME_WINDOW, err);
        return BME_WINDOW;
    }

    glfwMakeContextCurrent(window);

    err = glewInit();
    if (err != GLEW_OK) {
        CERR(BME_GLEW_INIT, err);
        return BME_GLEW_INIT;
    }

    coutAllInfo();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    std::array<glm::vec3, 3> triangule {
        glm::vec3 { -1.0f, -1.0f, 0.0f },
        glm::vec3 {  1.0f, -1.0f, 0.0f },
        glm::vec3 {  0.0f,  1.0f, 0.0f }
    };

    GLuint trianguleBuffer = sceneSingleTriangule1(triangule);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawScene(trianguleBuffer, 0, 3, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &trianguleBuffer);
    glfwTerminate();

    return 0;
}
