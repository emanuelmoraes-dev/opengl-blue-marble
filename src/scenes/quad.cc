#include "scenes.hh"

#include <array>

void loadQuad(GLuint* vao, GLsizei* vn, GLsizei* in) {
    std::array<Vertex, 4> quad {
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
            glm::vec3 {  1.0f,  1.0f, 0.0f },
            glm::vec3 {  1.0f,  0.0f, 0.0f },
            glm::vec2 {  1.0f,  1.0f }
        },

        Vertex {
            glm::vec3 { -1.0f,  1.0f, 0.0f },
            glm::vec3 {  0.0f,  0.0f, 1.0f },
            glm::vec2 {  0.0f,  1.0f }
        }
    };

    *vn = (GLsizei) quad.size();

    std::array<glm::ivec3, 2> indexes {
        glm::ivec3 { 0, 1, 3 },
        glm::ivec3 { 3, 1, 2 }
    };

    *in = (GLsizei) (indexes.size() * 3);

    GLuint vbo = 0;
    sceneVBO(&vbo, sizeof(quad), quad.data());

    GLuint ebo = 0;
    sceneEBO(&ebo, sizeof(indexes), indexes.data());

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

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
