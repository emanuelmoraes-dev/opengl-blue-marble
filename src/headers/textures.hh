#ifndef _OPENGL_BLUE_MARBLE_TEXTURES_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_TEXTURES_HH_INCLUDED_

#include "env.hh"
#include "os.hh"

#include <GL/glew.h>

#define BM_TEXTURE_EARTH BM_ENV_TEXTURES_DIR BM_SLASH "earth_2k.jpg"

int loadTexture(GLuint* textureId, const char* textureFile);

#endif
