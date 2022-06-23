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

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

glm::mat4 buildModelViewProjection() {
    // Model
    const glm::mat4 model = glm::identity<glm::mat4>();

    // View
    const glm::vec3 eye { 0.0f, 0.0f, 5.0f };
    const glm::vec3 center { 0.0f, 0.0f, 0.0f };
    const glm::vec3 up { 0, 1, 0 };
    const glm::mat4 view = glm::lookAt(eye, center, up);

    // Projection
    constexpr float fov = glm::radians(45.0f);
    constexpr float aspect = BM_WINDOW_WIDTH / BM_WINDOW_HEIGHT;
    constexpr float near = 1.0f;
    constexpr float far = 100000.0f;
    const glm::mat4 projection = glm::perspective(fov, aspect, near, far);

    return projection * view * model;
}

void applyCpuModelViewProjection(Vertex& vertex, glm::mat4 const& modelViewProjection) {
    glm::vec4 projected { vertex.position, 1.0f };
    projected = modelViewProjection * projected;
    projected /= projected.w;
    vertex.position = projected;
}

void terminate(GLuint const* programId, GLuint const* trianguleBuffer) {
    if (programId != nullptr)
        glDeleteProgram(*programId);
    if (trianguleBuffer != nullptr)
        glDeleteBuffers(1, trianguleBuffer);
    glfwTerminate();
}

int main() {
    int err = 0;

    err = glfwInit();
    if (err != GLFW_TRUE) {
        CERR(BM_ERR_GLFW_INIT, err);
        terminate(nullptr, nullptr);
        return BM_ERR_GLFW_INIT;
    }

    GLFWwindow* window = glfwCreateWindow(BM_WINDOW_WIDTH, BM_WINDOW_HEIGHT, BM_WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        CERR(BM_ERR_WINDOW, err);
        terminate(nullptr, nullptr);
        return BM_ERR_WINDOW;
    }

    glfwMakeContextCurrent(window);

    err = glewInit();
    if (err != GLEW_OK) {
        CERR(BM_ERR_GLEW_INIT, err);
        terminate(nullptr, nullptr);
        return BM_ERR_GLEW_INIT;
    }

    err = coutAllInfo();
    if (err != 0) {
        terminate(nullptr, nullptr);
        return err;
    }

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    const glm::mat4 modelViewProjection = buildModelViewProjection();

    std::array<Vertex, 3> triangule {
        Vertex { glm::vec3 { -1.0f, -1.0f, 0.0f }, glm::vec3 { 1.0f, 0.0f, 0.0f } },
        Vertex { glm::vec3 {  1.0f, -1.0f, 0.0f }, glm::vec3 { 0.0f, 1.0f, 0.0f } },
        Vertex { glm::vec3 {  0.0f,  1.0f, 0.0f }, glm::vec3 { 0.0f, 0.0f, 1.0f } }
    };

    // std::array<glm::vec3, 3> triangule {
    //     glm::vec3 { -1.0f, -1.0f, 0.0f },
    //     glm::vec3 {  1.0f, -1.0f, 0.0f },
    //     glm::vec3 {  0.0f,  1.0f, 0.0f }
    // };

    // std::array<glm::vec3, 6> triangule {
    //     glm::vec3 { -1.0f, -1.0f, 0.0f },
    //     glm::vec3 {  1.0f, -1.0f, 0.0f },
    //     glm::vec3 {  0.0f,  1.0f, 0.0f },

    //     glm::vec3 { -1.0f,  1.0f, 0.0f },
    //     glm::vec3 {  1.0f,  1.0f, 0.0f },
    //     glm::vec3 {  0.0f, -1.0f, 0.0f }
    // };

    // for (Vertex& vertex : triangule)
    //     applyCpuModelViewProjection(vertex, modelViewProjection);

    GLuint programId;
    err = loadShaders(&programId, BM_SHADER_VERT_TRIANGULE, BM_SHADER_FRAG_TRIANGULE);
    if (err != 0) {
        CERR_MSG(BM_ERR_LOAD_SHADERS, err, "triangule program error");
        terminate(nullptr, nullptr);
        return BM_ERR_LINK_PROGRAM;
    }

    const GLuint trianguleBuffer = sceneSingleTriangules(sizeof(triangule), triangule.data());

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);

        GLint MVP = glGetUniformLocation(programId, "MVP");
        glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(modelViewProjection));

        glBindBuffer(GL_ARRAY_BUFFER, trianguleBuffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex),
            reinterpret_cast<void*>(offsetof(Vertex, color)));

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    terminate(&programId, &trianguleBuffer);

    return 0;
}
