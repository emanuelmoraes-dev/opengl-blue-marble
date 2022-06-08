#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <stb_image.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {
    glfwInit();
    glewInit();
    glm::vec3 v {1, 2, 3};
    std::cout << glm::to_string(v) << std::endl;
    return 0;
}
