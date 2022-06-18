#ifndef _BLUE_MARBLE_SHADERS_HH_INCLUDED_
#define _BLUE_MARBLE_SHADERS_HH_INCLUDED_

#include "env.hh"
#include "os.hh"

#include <GL/glew.h>

#define BM_SHADER_VERT_TRIANGULE BM_ENV_SHADERS_DIR BM_SLASH "triangule_vert.glsl"
#define BM_SHADER_FRAG_TRIANGULE BM_ENV_SHADERS_DIR BM_SLASH "triangule_frag.glsl"

int loadShaders(GLuint* programId, const char* vertShaderFile, const char* fragShaderFile);

#endif
