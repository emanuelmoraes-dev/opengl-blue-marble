#include "scenes.hh"

#include <vector>

#include <glm/ext.hpp>

void genSphereVertexes(std::vector<Vertex>& vertexes, GLuint resolution) {
    vertexes.clear();

    if (resolution < 2)
        return;

    constexpr float PI = glm::pi<float>();
    constexpr float TWO_PI = glm::two_pi<float>();
    const float INV_RESOLUTION = 1.0f / (resolution - 1);

    for (GLuint i = 0; i < resolution; i++) {
        const float U = i * INV_RESOLUTION;
        const float PHI = glm::mix(0.0f, TWO_PI, U);

        for (GLuint j = 0; j < resolution; j++) {
            const float V = j * INV_RESOLUTION;
            const float THETA = glm::mix(0.0f, PI, V);

            glm::vec3 position {
                glm::sin(THETA) * glm::cos(PHI),
                glm::sin(THETA) * glm::sin(PHI),
                glm::cos(THETA)
            };

            glm::vec3 color { 1.0f, 1.0f, 1.0f };
            glm::vec2 uv { U, V };

            const Vertex vertex {position, color, uv};
            vertexes.push_back(vertex);
        }
    }
}

void loadSphere(GLuint* vao, GLsizei* size, GLuint resolution) {
    std::vector<Vertex> vertexes;
    genSphereVertexes(vertexes, resolution);
    *size = (GLsizei) vertexes.size();

    const GLsizei vboSize = (*size) * sizeof(Vertex);
    GLuint vbo = 0;
    sceneVBO(&vbo, vboSize, vertexes.data());

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex),
        (const void*) offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex),
        (const void*) offsetof(Vertex, uv));

    glBindVertexArray(0);
}
