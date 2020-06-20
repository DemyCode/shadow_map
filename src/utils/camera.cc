//
// Created by mehdi on 20/06/2020.
//

#include <glm/gtc/matrix_transform.hpp>
#include "camera.hh"

Camera::Camera(glm::vec3 position, glm::vec3 front_, glm::vec3 up) {
    this->position_ = position;
    this->front_ = front_;
    this->up_ = up;
}

glm::mat4 Camera::get_view() {
    return glm::lookAt(position_, position_ + front_, up_);
}