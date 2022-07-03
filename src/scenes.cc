#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "errors.hh"
#include "scenes.hh"

void sceneVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer) {
    glGenBuffers(1, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertexBuffer, GL_STATIC_DRAW);

    glBindBuffer(*vbo, 0);
}

void sceneEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer) {
    glGenBuffers(1, ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, elementBuffer, GL_STATIC_DRAW);

    glBindBuffer(*ebo, 0);
}

void loadQuad(GLuint* vao, GLsizei* size) {
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

    std::array<glm::ivec3, 2> indexes {
        glm::ivec3 { 0, 1, 3 },
        glm::ivec3 { 3, 1, 2 }
    };

    *size = (GLsizei) (indexes.size() * 3);

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
