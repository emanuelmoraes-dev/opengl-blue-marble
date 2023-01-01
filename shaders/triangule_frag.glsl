#version 330 core

uniform sampler2D TEX_EARTH;

in vec3 normal;
// in vec3 color;
in vec2 uv;

out vec4 outColor;

void main() {
    // outColor = vec4(color, 1.0);

    vec3 texColor = texture(TEX_EARTH, uv).rgb;
    outColor = vec4(texColor, 1.0f);
    // outColor = vec4(normalize(normal), 1.0f);
}
