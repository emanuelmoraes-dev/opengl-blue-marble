#include <iostream>
#include <array>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "errors.hh"
#include "window.hh"
#include "info.hh"
#include "scenes.hh"
#include "shaders.hh"
#include "fs.hh"

glm::mat4 buildModelViewProjection() {
    // Model
    const glm::mat4 model = glm::identity<glm::mat4>();

    // View
    const glm::vec3 eye { 10.0f, 10.0f, 10.0f };
    const glm::vec3 center { 0.0f, 0.0f, 0.0f };
    const glm::vec3 up { 0, 1, 0 };
    const glm::mat4 view = glm::lookAt(eye, center, up);

    // Projection
    constexpr float fov = glm::radians(45.0f);
    constexpr float aspect = BM_WINDOW_WIDTH / BM_WINDOW_HEIGHT;
    constexpr float near = 0.01f;
    constexpr float far = 1000.0f;
    const glm::mat4 projection = glm::perspective(fov, aspect, near, far);

    return projection * view * model;
}

void applyCpuModelViewProjection(glm::vec3& vertex, glm::mat4 const& modelViewProjection) {
    glm::vec4 projected { vertex, 1.0f };
    projected = modelViewProjection * projected;
    projected /= projected.w;
    vertex = projected;
}

int main() {
    int err = 0;

    err = glfwInit();
    if (err != GLFW_TRUE) {
        CERR(BM_ERR_GLFW_INIT, err);
        return BM_ERR_GLFW_INIT;
    }

    GLFWwindow* window = glfwCreateWindow(BM_WINDOW_WIDTH, BM_WINDOW_HEIGHT, BM_WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        CERR(BM_ERR_WINDOW, err);
        return BM_ERR_WINDOW;
    }

    glfwMakeContextCurrent(window);

    err = glewInit();
    if (err != GLEW_OK) {
        CERR(BM_ERR_GLEW_INIT, err);
        return BM_ERR_GLEW_INIT;
    }

    coutAllInfo();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    const glm::mat4 modelViewProjection = buildModelViewProjection();

    std::array<glm::vec3, 3> triangule {
        glm::vec3 { -1.0f, -1.0f, 0.0f },
        glm::vec3 {  1.0f, -1.0f, 0.0f },
        glm::vec3 {  0.0f,  1.0f, 0.0f }
    };

    std::string trianguleVertShader;
    err = readFile(BM_SHADER_VERT_TRIANGULE, trianguleVertShader);
    if (err != 0) {
        CERR(BM_ERR_FILE_NOT_FOUND, err);
        return BM_ERR_FILE_NOT_FOUND;
    }

    std::cout << trianguleVertShader << std::endl;

    for (glm::vec3& vertex : triangule)
        applyCpuModelViewProjection(vertex, modelViewProjection);

    // std::array<glm::vec3, 6> triangule {
    //     glm::vec3 { -1.0f, -1.0f, 0.0f },
    //     glm::vec3 {  1.0f, -1.0f, 0.0f },
    //     glm::vec3 {  0.0f,  1.0f, 0.0f },

    //     glm::vec3 { -1.0f,  1.0f, 0.0f },
    //     glm::vec3 {  1.0f,  1.0f, 0.0f },
    //     glm::vec3 {  0.0f, -1.0f, 0.0f }
    // };

    const GLuint trianguleBuffer = sceneSingleTriangules(sizeof(triangule), triangule.data());

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        drawScene(trianguleBuffer, 0, 3, 0, 3);
        // drawScene(trianguleBuffer, 0, 6, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &trianguleBuffer);
    glfwTerminate();

    return 0;
}
