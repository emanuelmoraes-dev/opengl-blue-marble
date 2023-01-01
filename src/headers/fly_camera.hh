#ifndef _OPENGL_BLUE_MARBLE_FLY_CAMERA_HH_INCLUDED_
#define _OPENGL_BLUE_MARBLE_FLY_CAMERA_HH_INCLUDED_

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class FlyCamera {
public:
    const glm::mat4 I;

    glm::vec3 _eye;
    glm::vec3 _direction;
    glm::vec3 _up;

    float _fov;
    float _aspect;
    float _near;
    float _far;

    float _speed;
    float _sensitivity;

    FlyCamera();
    glm::mat4 buildView() const;
    glm::mat4 buildProjection() const;
    void moveFoward(float amount);
    void moveRight(float amount);
    void look(float yaw, float pitch);
};

#endif
