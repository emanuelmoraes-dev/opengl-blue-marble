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

    vec3 v = vec3(0.0, 0.0, 1.0);
    vec3 r = reflect(-l, n);
    float alpha = 50.0; // ex: 2, 10, 50, 250, 1250
    float specularIntensity = 0.60;
    float specular = pow(max(dot(r, v), 0.0), alpha);
    specular = max(specular, 0.0) * specularIntensity;

    vec3 texColor = texture(TEX_EARTH, uv).rgb;
    outColor = vec4(texColor * LIGHT_INTENSITY * lambertian + specular, 1.0f);
}
