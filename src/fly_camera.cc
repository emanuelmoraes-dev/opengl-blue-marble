#include "fly_camera.hh"
#include "window.hh"

#include <iostream>

FlyCamera::FlyCamera() :
    _eye(glm::vec3{ 0.0f, 0.0f, 5.0f }),
    _direction(glm::vec3{ 0.0f, 0.0f, -1.0f }),
    _up(glm::vec3{ 0, 1, 0 }),

    _fov(glm::radians(45.0f)),
    _aspect(BM_WINDOW_WIDTH / BM_WINDOW_HEIGHT),
    _near(0.01f),
    _far(1000.0f),

    _speed(2.0f) {}

glm::mat4 FlyCamera::buildViewProjection() const {
    const glm::mat4 view = glm::lookAt(_eye, _eye + _direction, _up);
    const glm::mat4 projection = glm::perspective(_fov, _aspect, _near, _far);
    return projection * view;
}

void FlyCamera::moveFoward(float amount) {
    const glm::vec3 direction = glm::normalize(_direction);
    _eye += direction * amount * _speed;
}

void FlyCamera::moveRight(float amount) {
    const glm::vec3 right = glm::normalize(glm::cross(_direction, _up));
   _eye += right * amount * _speed * (-1.0f);
}
