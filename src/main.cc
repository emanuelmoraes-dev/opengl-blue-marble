#include <iostream>
#include <GLFW/glfw3.h>

#include "errors.hh"
#include "window.hh"

int main() {
    int err = 0;

    err = glfwInit();
    if (err == GLFW_FALSE) {
        std::cerr << BME_GLFW_INIT_MESSAGE << std::endl;
        return BME_GLFW_INIT;
    }

    GLFWwindow* window = glfwCreateWindow(BMW_WIDTH, BMW_HEIGHT, BMW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << BME_WINDOW_MESSAGE << std::endl;
        return BME_WINDOW;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
