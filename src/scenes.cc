#include "scenes.hh"

#include <GL/glew.h>

void drawScene(GLuint vertexBuffer, GLuint drawIndex, GLuint drawSize, GLuint vertexIndex, GLuint vertexSize) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(vertexIndex, vertexSize, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, drawIndex, drawSize);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
