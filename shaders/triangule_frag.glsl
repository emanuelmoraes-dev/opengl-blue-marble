#version 330 core

in vec3 color;
in vec2 uv;

out vec4 outColor;

void main() {
    // outColor = vec4(color, 1.0);
    outColor = vec4(uv, 0.0f, 1.0f);
}
