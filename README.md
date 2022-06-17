# OpenGL Blue Marble
OpenGL project to show the Earth

## Building
To be able to compile the source code, follow the instructions below

### Dependencies
* [OpenGL](https://www.opengl.org)
  * Note: It is possible that your operating system already provides this library
* [GLEW](http://glew.sourceforge.net)
  * Note: For Windows environments extract in "libs/glew"
  * Note: For Windows environments the "glew32.dll" must to be in the binary folder OR in the %PATH% variable
* [GLFW](https://www.glfw.org)
  * Note: For Windows environments extract in "libs/glfw"

### Configuring Environment
Copy the file "env/env.example.hh" in "env/debug/env.hh" and "env/release/env.hh" with the configuration for debug and release environments respectively

#### env.hh
* BM_ENV_SHADERS_DIR: Folder path that has the shading source
