#ifndef _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_

#include <iostream>

#define CERR(BME, EXE) std::cerr << "[Error " << BME << "/" << EXE << "]: " << BME##_MESSAGE << std::endl
#define CERR_PANIC(MESSAGE) std::cerr << "[Panic]: " << MESSAGE << std::endl

#define __BM_ERRBASE (30) // internal errors should to start in 30

#define BME_PANIC (__BM_ERRBASE + 0)

#define BME_GLFW_INIT (__BM_ERRBASE + 1)
#define BME_GLFW_INIT_MESSAGE "GLFW wasn't initialized"

#define BME_WINDOW (__BM_ERRBASE + 2)
#define BME_WINDOW_MESSAGE "The window wasn't created"

#define BME_GLEW_INIT (__BM_ERRBASE + 3)
#define BME_GLEW_INIT_MESSAGE "The GLEW wasn't initialized"

#endif