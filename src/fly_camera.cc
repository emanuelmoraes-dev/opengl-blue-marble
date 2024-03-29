#include "fly_camera.hh"
#include "window.hh"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

FlyCamera::FlyCamera() :
    I(glm::identity<glm::mat4>()),

    _eye(glm::vec3{ 0.0f, 0.0f, 5.0f }),
    _direction(glm::vec3{ 0.0f, 0.0f, -1.0f }),
    _up(glm::vec3{ 0.0f, 1.0f, 0.0f }),

    _fov(glm::radians(45.0f)),
    _aspect(BM_INIT_WINDOW_WIDTH / BM_INIT_WINDOW_HEIGHT),
    _near(0.01f),
    _far(1000.0f),

    _speed(4.0f),
    _sensitivity(0.1f) {}

glm::mat4 FlyCamera::buildView() const {
    return glm::lookAt(_eye, _eye + _direction, _up);
}

glm::mat4 FlyCamera::buildProjection() const {
    return glm::perspective(_fov, _aspect, _near, _far);
}

void FlyCamera::moveFoward(float amount) {
    const glm::vec3 direction = glm::normalize(_direction);
    _eye += direction * amount * _speed;
}

void FlyCamera::moveRight(float amount) {
    const glm::vec3 right = glm::normalize(glm::cross(_direction, _up));
   _eye += right * amount * _speed * (-1.0f);
}

void FlyCamera::look(float yaw, float pitch) {
    // axes
    const glm::vec3 direction = glm::normalize(_direction);
    const glm::vec3 up = glm::normalize(_up);
    const glm::vec3 right = glm::normalize(glm::cross(direction, up));

    // rotate matrixes
    const glm::mat4 yawRotate = glm::rotate(I, glm::radians(yaw * _sensitivity), up);
    const glm::mat4 pitchRotate = glm::rotate(I, glm::radians(pitch * _sensitivity), right);

    // update
    _up = glm::normalize(pitchRotate * glm::vec4 { up, 0.0f });
    _direction = glm::normalize(yawRotate * pitchRotate * glm::vec4 { direction, 0.0f });
}
