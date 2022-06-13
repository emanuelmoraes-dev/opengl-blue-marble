#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "errors.hh"
#include "scenes.hh"

GLuint sceneSingleTriangules(GLsizeiptr size, const void* triangule) {
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, triangule, GL_STATIC_DRAW);

    glBindBuffer(vertexBuffer, 0);
    return vertexBuffer;
}
