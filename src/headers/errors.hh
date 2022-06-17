#ifndef _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_

#include <iostream>

#define CERR(BME, EXE) std::cerr << "[Error " << BME << "/" << EXE << "]: " << BME##_MESSAGE << std::endl
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

#endif
