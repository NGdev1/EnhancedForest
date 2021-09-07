//
//  Vertex.h
//  EnhancedForest
//
//  Created by Admin on 12.08.2021.
//

#pragma once

namespace ef {

struct vec2 {
    float x, y;

    vec2(const float& x, const float& y)
            : x(x)
            , y(y) {}

    vec2()
        : x(0)
        , y(0) {}
};

struct vec3 {
    float x, y, z;

    vec3(const float& x, const float& y, const float& z)
            : x(x)
            , y(y)
            , z(z) {}
    vec3()
        : x(0)
        , y(0)
        , z(0) {}
};

struct mat4row {
    float values[4];

    float &operator[](const unsigned int index) {
        return values[index];
    }

    mat4row() : values {0.f, 0.f, 0.f, 0.f} {}
};

struct mat4 {
    mat4row rows[4];

    mat4row &operator[](const unsigned int index) {
        return rows[index];
    }

    mat4(const float& scale) {
        rows[0][0] = scale;
        rows[1][1] = scale;
        rows[2][2] = scale;
        rows[3][3] = scale;
    }

    mat4() {}
};

struct Vertex {
    // position
    vec3 position;
    // texCoords
    vec2 texCoords;

    Vertex(const vec3& position, const vec2& texCoords)
            : position(position)
            , texCoords(texCoords){};
};

} // namespace ef
