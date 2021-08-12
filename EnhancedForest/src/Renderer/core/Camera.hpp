//
//  Camera.hpp
//  Neverland
//
//  Created by Admin on 21.07.2021.
//

#pragma once

#include "Common.h"

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
    vec3 position;
    vec2 rotation;

public:
    Camera();
    mat4 getViewMatrix();
};
