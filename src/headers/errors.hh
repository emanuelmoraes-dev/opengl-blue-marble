#ifndef _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_ERRORS_HH_INCLUDED_

#define __BM_ERRBASE (30) // internal errors should to start in 30

#define BME_PANIC (__BM_ERRBASE + 0)
#define BME_PANIC_MESSAGE "Unknow Error"

#define BME_GLFW_INIT (__BM_ERRBASE + 1)
#define BME_GLFW_INIT_MESSAGE "GLFW wasn't initialized"

#define BME_WINDOW (__BM_ERRBASE + 2)
#define BME_WINDOW_MESSAGE "The window wasn't created"

#endif