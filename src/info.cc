#include "info.hh"
#include "errors.hh"

#include <GL/glew.h>

void coutGlVersion() {
    GLint glMajorVersion = -1;
    GLint glMinorVersion = -1;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &glMinorVersion);

    if (glMajorVersion == -1 || glMinorVersion == -1) {
        CERR_PANIC("OpenGL version could not be obtained!");
        exit(BME_PANIC);
    }

    const GLubyte* glFullVersion = glGetString(GL_VERSION);
    if (glFullVersion == nullptr) {
        CERR_PANIC("Full OpenGL version could not be obtained!");
        exit(BME_PANIC);
    }

    std::cout << "OpenGL version: " << glMajorVersion << "." << glMinorVersion << std::endl;
    std::cout << "Full OpenGL version: " << glFullVersion << std::endl;
}

void coutGlslVersion() {
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    if (glslVersion == nullptr) {
        CERR_PANIC("GLSF VERSION could not be obtained!");
        exit(BME_PANIC);
    }

    std::cout << "GLSF version: " << glslVersion << std::endl;
}

void coutGlVendor() {
    const GLubyte* glVendor = glGetString(GL_VENDOR);

    if (glVendor == nullptr) {
        CERR_PANIC("OpenGL vendor could not be obtained!");
        exit(BME_PANIC);
    }

    std::cout << "OpenGL vendor: " << glVendor << std::endl;
}

void coutGlRenderer() {
    const GLubyte* glRenderer = glGetString(GL_RENDERER);

    if (glRenderer == nullptr) {
        CERR_PANIC("OpenGL renderer could not be obtained!");
        exit(BME_PANIC);
    }

    std::cout << "OpenGL vendor: " << glRenderer << std::endl;
}

void coutAllInfo() {
   coutGlVersion();
   coutGlslVersion();
   coutGlVendor();
   coutGlRenderer();
}