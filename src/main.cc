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
#include "textures.hh"
#include "fly_camera.hh"
#include "delta.hh"

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 uv;
};

void terminate(GLuint const* programId, GLuint const* trianguleBuffer) {
    glUseProgram(0);
    if (programId != nullptr)
        glDeleteProgram(*programId);
    if (trianguleBuffer != nullptr)
        glDeleteBuffers(1, trianguleBuffer);
    glfwTerminate();
}

// glm::mat4 buildModelViewProjection() {
//     // Model
//     const glm::mat4 model = glm::identity<glm::mat4>();

//     // View
//     const glm::vec3 eye { 0.0f, 0.0f, 5.0f };
//     const glm::vec3 center { 0.0f, 0.0f, 0.0f };
//     const glm::vec3 up { 0, 1, 0 };
//     const glm::mat4 view = glm::lookAt(eye, center, up);

//     // Projection
//     constexpr float fov = glm::radians(45.0f);
//     constexpr float aspect = BM_WINDOW_WIDTH / BM_WINDOW_HEIGHT;
//     constexpr float near = 1.0f;
//     constexpr float far = 100000.0f;
//     const glm::mat4 projection = glm::perspective(fov, aspect, near, far);

//     return projection * view * model;
// }

// void applyCpuModelViewProjection(Vertex& vertex, glm::mat4 const& modelViewProjection) {
//     glm::vec4 projected { vertex.position, 1.0f };
//     projected = modelViewProjection * projected;
//     projected /= projected.w;
//     vertex.position = projected;
// }

FlyCamera camera;
DeltaF dtime;
DeltaF dyaw;
DeltaF dpitch;
bool changingDirection = false;

void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double x;
            double y;
            glfwGetCursorPos(window, &x, &y);
            dyaw.tick((float) x);
            dpitch.tick((float) y);
            changingDirection = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            dyaw.reset();
            dpitch.reset();
            changingDirection = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
    if (changingDirection) {
        dyaw.tick((float) x);
        dpitch.tick((float) y);
        camera.look(dyaw.delta(), dpitch.delta());
    }
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

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
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

    const glm::mat4 model = glm::identity<glm::mat4>();
    // const glm::mat4 modelViewProjection = buildModelViewProjection();

    std::array<Vertex, 6> triangules {
        Vertex {
            glm::vec3 { -1.0f, -1.0f, 0.0f },
            glm::vec3 {  1.0f,  0.0f, 0.0f },
            glm::vec2 {  0.0f,  0.0f }
        },

        Vertex {
            glm::vec3 {  1.0f, -1.0f, 0.0f },
            glm::vec3 {  0.0f,  1.0f, 0.0f },
            glm::vec2 {  1.0f,  0.0f }
        },

        Vertex {
            glm::vec3 { -1.0f,  1.0f, 0.0f },
            glm::vec3 {  0.0f,  0.0f, 1.0f },
            glm::vec2 {  0.0f,  1.0f }
        },

        Vertex {
            glm::vec3 { -1.0f,  1.0f, 0.0f },
            glm::vec3 {  0.0f,  0.0f, 1.0f },
            glm::vec2 {  0.0f,  1.0f }
        },

        Vertex {
            glm::vec3 {  1.0f, -1.0f, 0.0f },
            glm::vec3 {  0.0f,  1.0f, 0.0f },
            glm::vec2 {  1.0f,  0.0f }
        },

        Vertex {
            glm::vec3 {  1.0f,  1.0f, 0.0f },
            glm::vec3 {  1.0f,  0.0f, 0.0f },
            glm::vec2 {  1.0f,  1.0f }
        },
    };

    // for (Vertex& vertex : triangules)
    //     applyCpuModelViewProjection(vertex, modelViewProjection);

    GLuint programId;
    err = loadShaders(&programId, BM_SHADER_VERT_TRIANGULE, BM_SHADER_FRAG_TRIANGULE);
    if (err != 0) {
        CERR_MSG(BM_ERR_LOAD_SHADERS, err, "triangule program error");
        terminate(nullptr, nullptr);
        return BM_ERR_LINK_PROGRAM;
    }

    GLuint earthTextureId = 0;
    err = loadTexture(&earthTextureId, BM_TEXTURE_EARTH);
    if (err != 0) {
        CERR_MSG(BM_ERR_LOAD_TEXTURE, err, "earth texture error");
        terminate(&programId, nullptr);
        return err;
    }

    const GLuint trianguleBuffer = sceneSingleTriangules(sizeof(triangules), triangules.data());

    dtime.tick((float) glfwGetTime());

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (!glfwWindowShouldClose(window)) {
        dtime.tick((float) glfwGetTime());

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programId);

        const glm::mat4 modelViewProjection = camera.buildViewProjection() * model;
        GLint MVP = glGetUniformLocation(programId, "MVP");
        glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(modelViewProjection));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthTextureId);

        GLuint TEX_EARTH = glGetUniformLocation(programId, "TEX_EARTH");
        glUniform1f(TEX_EARTH, 0);

        glBindBuffer(GL_ARRAY_BUFFER, trianguleBuffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex),
            (const void*) offsetof(Vertex, color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex),
            (const void*) offsetof(Vertex, uv));

        glPointSize(10.0f);
        glLineWidth(10.0f);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // glDrawArrays(GL_POINT, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_LINE, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_LINE_LOOP, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) triangules.size());
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) triangules.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);

        glfwPollEvents();
        glfwSwapBuffers(window);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.moveFoward(1 * dtime.delta());
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.moveFoward(-1 * dtime.delta());

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.moveRight(1 * dtime.delta());
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.moveRight(-1 * dtime.delta());
    }

    terminate(&programId, &trianguleBuffer);

    return 0;
}
