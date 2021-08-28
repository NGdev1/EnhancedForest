//
//  Camera.hpp
//  Neverland
//
//  Created by Admin on 21.07.2021.
//

#pragma once

#include <glm/glm.hpp>

namespace ef {

class Camera {
    void updateVectors();

public:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    glm::vec3 position;
    glm::mat4 rotation;
    Camera(glm::vec3 position);

    void rotate(float x, float y, float z);

    glm::mat4 getView();
};

} // namespace ef
