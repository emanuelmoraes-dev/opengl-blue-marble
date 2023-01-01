#version 330 core

uniform sampler2D TEX_EARTH;
uniform vec3 LIGHT_DIRECTION;
uniform float LIGHT_INTENSITY;

in vec3 normal;
// in vec3 color;
in vec2 uv;

out vec4 outColor;

void main() {
    // outColor = vec4(color, 1.0);

    vec3 n = normalize(normal);
    vec3 l = -normalize(LIGHT_DIRECTION);
    float lambertian = max(dot(n, l), 0.0);

    vec3 texColor = texture(TEX_EARTH, uv).rgb;
    outColor = vec4(texColor * LIGHT_INTENSITY * lambertian, 1.0f);
}
