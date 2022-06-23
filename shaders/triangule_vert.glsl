#version 330 core

uniform mat4 MVP;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;

out vec3 color;

void main() {
    color = inColor;
    gl_Position = MVP * vec4(inPosition, 1.0);
}
