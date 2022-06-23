#ifndef _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_

#include <iostream>

#define CERR(BME, CAUSE) std::cerr << "[Error " << BME << "/" << CAUSE << "]: " << BME##_MESSAGE << std::endl
#define CERR_MSG(BME, CAUSE, MSG) std::cerr << "[Error " << BME << "/" << CAUSE << "]: " << BME##_MESSAGE << ": " << MSG << std::endl
#define CERR_PANIC(MESSAGE) std::cerr << "[Panic]: " << MESSAGE << std::endl

#define __BM_ERRBASE (30) // internal errors should to start in 30

#define BM_ERR_PANIC (__BM_ERRBASE + 0)

#define BM_ERR_GLFW_INIT (__BM_ERRBASE + 1)
#define BM_ERR_GLFW_INIT_MESSAGE "GLFW wasn't initialized"

#define BM_ERR_WINDOW (__BM_ERRBASE + 2)
#define BM_ERR_WINDOW_MESSAGE "The window wasn't created"

#define BM_ERR_GLEW_INIT (__BM_ERRBASE + 3)
#define BM_ERR_GLEW_INIT_MESSAGE "The GLEW wasn't initialized"

#define BM_ERR_FILE_NOT_FOUND (__BM_ERRBASE + 4)
#define BM_ERR_FILE_NOT_FOUND_MESSAGE "File not found"

#define BM_ERR_LOAD_SHADERS (__BM_ERRBASE + 5)
#define BM_ERR_LOAD_SHADERS_MESSAGE "Error loading program"

#define BM_ERR_SHADER_COMPILE_PANIC (__BM_ERRBASE + 6)
#define BM_ERR_SHADER_COMPILE_PANIC_MESSAGE "Compile shader fails without logs"

#define BM_ERR_SHADER_COMPILE (__BM_ERRBASE + 7)
#define BM_ERR_SHADER_COMPILE_MESSAGE "Shader failed"

#define BM_ERR_VERT_SHADER_COMPILE (__BM_ERRBASE + 8)
#define BM_ERR_VERT_SHADER_COMPILE_MESSAGE "Vertex shader failed"

#define BM_ERR_FRAG_SHADER_COMPILE (__BM_ERRBASE + 9)
#define BM_ERR_FRAG_SHADER_COMPILE_MESSAGE "Fragment shader failed"

#define BM_ERR_LINK_PROGRAM_PANIC (__BM_ERRBASE + 10)
#define BM_ERR_LINK_PROGRAM_PANIC_MESSAGE "Error linking program without logs"

#define BM_ERR_LINK_PROGRAM (__BM_ERRBASE + 11)
#define BM_ERR_LINK_PROGRAM_MESSAGE "Error linking program"

#define BM_ERR_STBI_LOAD (__BM_ERRBASE + 12)
#define BM_ERR_STBI_LOAD_MESSAGE "stb: Error loading image"

#define BM_ERR_LOAD_TEXTURE (__BM_ERRBASE + 13)
#define BM_ERR_LOAD_TEXTURE_MESSAGE "Error loading texture"

#endif
