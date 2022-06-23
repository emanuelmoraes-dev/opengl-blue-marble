#version 330 core

uniform mat4 MVP;

layout (location = 0) in vec3 inPosition;
// layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inUv;

// out vec3 color;
out vec2 uv;

void main() {
    // color = inColor;
    uv = inUv;
    gl_Position = MVP * vec4(inPosition, 1.0);
}
