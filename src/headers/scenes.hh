#ifndef _OPENGL_BLUE_MARBLE_SCENES_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_SCENES_HH_INCLUDED_

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 uv;
};

void sceneVBO(GLuint* vbo, GLsizeiptr size, const void* vertexBuffer);
void sceneEBO(GLuint* ebo, GLsizeiptr size, const void* elementBuffer);

void loadQuad(GLuint* vao, GLsizei* vn, GLsizei* in);
void loadSphere(GLuint* vao, GLsizei* vn, GLsizei* in, GLuint resolution);


#endif
