#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "errors.hh"
#include "scenes.hh"

GLuint sceneSingleTriangule1(std::array<glm::vec3, 3> const& triangule) {
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangule), triangule.data(), GL_STATIC_DRAW);

    glBindBuffer(vertexBuffer, 0);
    return vertexBuffer;
}
