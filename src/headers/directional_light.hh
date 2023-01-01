#ifndef _OPENGL_BLUE_MARBLE_DIRECTIONAL_LIGHT_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_DIRECTIONAL_LIGHT_HH_INCLUDED_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct DirectionalLight {
    glm::vec3 direction;
    float intensity;
};

#endif