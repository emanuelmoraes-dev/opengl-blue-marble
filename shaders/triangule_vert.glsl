#version 330 core

uniform mat4 MVP;
uniform mat4 MV_NORMAL;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
// layout (location = 2) in vec3 inColor;
layout (location = 3) in vec2 inUv;

out vec3 normal;
// out vec3 color;
out vec2 uv;

void main() {
    // color = inColor;
    normal = vec3(MV_NORMAL * vec4(inNormal, 0.0));
    uv = inUv;
    gl_Position = MVP * vec4(inPosition, 1.0);
}
