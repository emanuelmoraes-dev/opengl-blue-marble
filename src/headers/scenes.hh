#ifndef _OPENGL_BLUE_MARBLE_SCENES_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_SCENES_HH_INCLUDED_

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

void sceneSingleTriangulesVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer);
void sceneSingleTriangulesEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer);

#endif
