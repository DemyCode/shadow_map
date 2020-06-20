//
// Created by mehdi on 20/06/2020.
//

#ifndef SHADOW_MAP_CAMERA_HH
#define SHADOW_MAP_CAMERA_HH


#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 front_, glm::vec3 up);
    glm::mat4 get_view();

    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
};


#endif //SHADOW_MAP_CAMERA_HH
