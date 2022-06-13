#ifndef _OPENGL_BLUE_MARBLE_SCENES_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_SCENES_HH_INCLUDED_

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

void drawScene(GLuint vertexBuffer, GLuint drawIndex, GLuint drawSize, GLuint vertexIndex, GLuint vertexSize);
GLuint sceneSingleTriangules(GLsizeiptr size, const void* triangule);

#endif
