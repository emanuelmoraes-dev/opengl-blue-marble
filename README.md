# OpenGL Blue Marble
OpenGL project to show the Earth

## Building
To be able to compile the source code, follow the instructions below

### Dependencies
* [GLM](https://glm.g-truc.net/0.9.9/index.html)
  * Note: It is already in the project
* [STB](https://github.com/nothings/stb)
  * Note: It is already in the project
* [OpenGL](https://www.opengl.org)
  * Note: It is possible that your operating system already provides this library
* [GLFW](https://www.glfw.org)
  * Note: For Windows environments extract in "libs/glfw"
  * Note: If you use Windows, you can download [here](https://github.com/emanuelmoraes-dev/opengl-blue-marble/releases/download/v1.0.0-windows_x86_amd64/glfw.zip)
* [GLEW](http://glew.sourceforge.net)
  * Note: For Windows environments extract in "libs/glew"
  * Note: For Windows environments the "glew32.dll" must to be in the binary folder OR in the %PATH% variable
  * Note: If you use Windows, you can download [here](https://github.com/emanuelmoraes-dev/opengl-blue-marble/releases/download/v1.0.0-windows_x86_amd64/glew.zip)

### Configuring Environment
Rename the files "env/debug/env.example.hh" and "env/release/env.example.hh" to "env/debug/env.hh" and "env/release/env.hh" (respectively) with the environments configurations

#### env/debug/env.hh and env/release/env.hh
* BM_ENV_SHADERS_DIR: Relative path (from the binary folder) that has the shading source
* BM_ENV_TEXTURES_DIR: Relative path (from the binary folder) that has the textures
