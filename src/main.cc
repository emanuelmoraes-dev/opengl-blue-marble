#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "errors.hh"
#include "window.hh"
#include "info.hh"

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
