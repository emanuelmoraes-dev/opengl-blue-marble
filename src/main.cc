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
#include "directional_light.hh"
#include "fs.hh"

// struct Vertex {
//     glm::vec3 position;
//     glm::vec3 color;
//     glm::vec2 uv;
// };

// void terminate(GLuint const* programId, GLuint const* vbo, GLuint const* ebo) {
//     glUseProgram(0);
//     if (programId != nullptr)
//         glDeleteProgram(*programId);
//     if (vbo != nullptr)
//         glDeleteBuffers(1, vbo);
//     if (ebo != nullptr)
//         glDeleteBuffers(1, ebo);
//     glfwTerminate();
// }

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

void terminate(GLuint const* programId, GLuint const* vao) {
    glUseProgram(0);
    if (programId != nullptr)
        glDeleteProgram(*programId);
    if (vao != nullptr)
        glDeleteVertexArrays(1, vao);
    glfwTerminate();
}

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

void resized(GLFWwindow* window, int width, int height) {
    camera._aspect = (float) width / height;
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

int main(int argc, const char* argv[]) {
    std::string exeDir;

    if (argc < 0)
        exeDir = ".";
    else
        exeDir = dir(argv[0]);

    int err = 0;

    err = glfwInit();
    if (err != GLFW_TRUE) {
        CERR(BM_ERR_GLFW_INIT, err);
        // terminate(nullptr, nullptr, nullptr);
        terminate(nullptr, nullptr);
        return BM_ERR_GLFW_INIT;
    }

    GLFWwindow* window = glfwCreateWindow(BM_INIT_WINDOW_WIDTH, BM_INIT_WINDOW_HEIGHT, BM_WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        CERR(BM_ERR_WINDOW, err);
        // terminate(nullptr, nullptr, nullptr);
        terminate(nullptr, nullptr);
        return BM_ERR_WINDOW;
    }

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetFramebufferSizeCallback(window, resized);

    glfwMakeContextCurrent(window);

    err = glewInit();
    if (err != GLEW_OK) {
        CERR(BM_ERR_GLEW_INIT, err);
        // terminate(nullptr, nullptr, nullptr);
        terminate(nullptr, nullptr);
        return BM_ERR_GLEW_INIT;
    }

    err = coutAllInfo();
    if (err != 0) {
        // terminate(nullptr, nullptr, nullptr);
        terminate(nullptr, nullptr);
        return err;
    }

    resized(window, BM_INIT_WINDOW_WIDTH, BM_INIT_WINDOW_HEIGHT);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    DirectionalLight light;
    light.direction = glm::vec3{ 0.0f, 0.0f, -1.0f };
    light.intensity = 1.0f;

    // const glm::mat4 modelViewProjection = buildModelViewProjection();
    const glm::mat4 identity = glm::identity<glm::mat4>();
    const glm::vec3 xAxe = glm::vec3 { 1.0f, 0.0f, 0.0f };
    const glm::mat4 model = glm::rotate(identity, glm::radians(90.0f), xAxe);

    // std::array<Vertex, 6> triangules {
    //     Vertex {
    //         glm::vec3 { -1.0f, -1.0f, 0.0f },
    //         glm::vec3 {  1.0f,  0.0f, 0.0f },
    //         glm::vec2 {  0.0f,  0.0f }
    //     },

    //     Vertex {
    //         glm::vec3 {  1.0f, -1.0f, 0.0f },
    //         glm::vec3 {  0.0f,  1.0f, 0.0f },
    //         glm::vec2 {  1.0f,  0.0f }
    //     },

    //     Vertex {
    //         glm::vec3 { -1.0f,  1.0f, 0.0f },
    //         glm::vec3 {  0.0f,  0.0f, 1.0f },
    //         glm::vec2 {  0.0f,  1.0f }
    //     },

    //     Vertex {
    //         glm::vec3 { -1.0f,  1.0f, 0.0f },
    //         glm::vec3 {  0.0f,  0.0f, 1.0f },
    //         glm::vec2 {  0.0f,  1.0f }
    //     },

    //     Vertex {
    //         glm::vec3 {  1.0f, -1.0f, 0.0f },
    //         glm::vec3 {  0.0f,  1.0f, 0.0f },
    //         glm::vec2 {  1.0f,  0.0f }
    //     },

    //     Vertex {
    //         glm::vec3 {  1.0f,  1.0f, 0.0f },
    //         glm::vec3 {  1.0f,  0.0f, 0.0f },
    //         glm::vec2 {  1.0f,  1.0f }
    //     },
    // };

    // sceneVBO(&quadVBO, sizeof(triangules), triangules.data());

    // for (Vertex& vertex : triangules)
    //     applyCpuModelViewProjection(vertex, modelViewProjection);

    // GLuint quadVAO = 0;
    // GLsizei quadVN = 0;
    // GLsizei quadIN = 0;
    // loadQuad(&quadVAO, &quadVN, &quadIN);

    GLuint sphereVAO = 0;
    GLsizei sphereVN = 0;
    GLsizei sphereIN = 0;
    loadSphere(&sphereVAO, &sphereVN, &sphereIN, 50);

    GLuint programId = 0;
    std::string vertShader = join(exeDir.c_str(), BM_SHADER_VERT_TRIANGULE);
    std::string fragShader = join(exeDir.c_str(), BM_SHADER_FRAG_TRIANGULE);
    err = loadShaders(&programId, vertShader.c_str(), fragShader.c_str());
    if (err != 0) {
        CERR_MSG(BM_ERR_LOAD_SHADERS, err, "triangule program error");
        // terminate(nullptr, nullptr, nullptr);
        terminate(nullptr, nullptr);
        return BM_ERR_LINK_PROGRAM;
    }

    GLuint earthTextureId = 0;
    std::string texEarth = join(exeDir.c_str(), BM_TEXTURE_EARTH);
    err = loadTexture(&earthTextureId, texEarth.c_str());
    if (err != 0) {
        CERR_MSG(BM_ERR_LOAD_TEXTURE, err, "earth texture error");
        // terminate(&programId, nullptr, nullptr);
        terminate(&programId, nullptr);
        return err;
    }

    GLuint cloudsTextureId = 0;
    std::string texClouds = join(exeDir.c_str(), BM_TEXTURE_CLOUDS);
    err = loadTexture(&cloudsTextureId, texClouds.c_str());
    if (err != 0) {
        CERR_MSG(BM_ERR_LOAD_TEXTURE, err, "clouds texture error");
        terminate(&programId, nullptr);
        return err;
    }

    dtime.tick((float) glfwGetTime());

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(window)) {
        dtime.tick((float) glfwGetTime());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);

        const glm::mat4 view = camera.buildView();
        const glm::mat4 projection = camera.buildProjection();
        const glm::mat4 modelViewProjection = projection * view * model;
        const GLint MVP = glGetUniformLocation(programId, "MVP");
        glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(modelViewProjection));

        const glm::mat4 modelViewNormal = glm::inverse(glm::transpose(view * model));
        const GLint MV_NORMAL = glGetUniformLocation(programId, "MV_NORMAL");
        glUniformMatrix4fv(MV_NORMAL, 1, GL_FALSE, glm::value_ptr(modelViewNormal));

        const glm::vec4 lightDirection = view * glm::vec4{light.direction, 0.0f};
        const GLint LIGHT_DIRECTION = glGetUniformLocation(programId, "LIGHT_DIRECTION");
        glUniform3fv(LIGHT_DIRECTION, 1, glm::value_ptr(lightDirection));

        const GLint LIGHT_INTENSITY = glGetUniformLocation(programId, "LIGHT_INTENSITY");
        glUniform1f(LIGHT_INTENSITY, light.intensity);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthTextureId);
        GLint TEX_EARTH = glGetUniformLocation(programId, "TEX_EARTH");
        glUniform1i(TEX_EARTH, 0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cloudsTextureId);
        GLint TEX_CLOUDS = glGetUniformLocation(programId, "TEX_CLOUDS");
        glUniform1i(TEX_CLOUDS, 1);

        GLint TIME = glGetUniformLocation(programId, "TIME");
        glUniform1f(TIME, (float) glfwGetTime());

        // glBindBuffer(GL_ARRAY_BUFFER, trianguleBuffer);

        // glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);

        // glEnableVertexAttribArray(0);
        // glEnableVertexAttribArray(1);
        // glEnableVertexAttribArray(2);

        // glBindVertexArray(quadVAO);
        glBindVertexArray(sphereVAO);

        glPointSize(10.0f);
        glLineWidth(10.0f);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        // glDrawArrays(GL_POINTS, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_LINES, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_LINE_LOOP, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) triangules.size());
        // glDrawArrays(GL_TRIANGLES, 0, (GLsizei) triangules.size());

        // glDrawElements(GL_TRIANGLES, quadIN, GL_UNSIGNED_INT, nullptr);
        // glDrawArrays(GL_POINTS, 0, sphereVN);

        glDrawElements(GL_TRIANGLES, sphereIN, GL_UNSIGNED_INT, nullptr);

        // glDisableVertexAttribArray(0);
        // glDisableVertexAttribArray(1);
        // glDisableVertexAttribArray(2);
        // glBindBuffer(GL_ARRAY_BUFFER, 0);
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
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

    // terminate(&programId, &quadVBO, &quadEBO);
    // terminate(&programId, &quadVAO);
    terminate(&programId, &sphereVAO);

    return 0;
}
