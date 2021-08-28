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

    vec2(float x, float y)
        : x(x)
        , y(y) {}

    vec2()
        : x(0)
        , y(0) {}
};

struct vec3 {
    float x, y, z;

    vec3(float x, float y, float z)
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

    mat4row() {
        values[0] = 0.f;
        values[1] = 0.f;
        values[2] = 0.f;
        values[3] = 0.f;
    }
};

struct mat4 {
    mat4row rows[4];

    mat4row &operator[](const unsigned int index) {
        return rows[index];
    }

    mat4(float scale) {
        rows[0][0] = scale;
        rows[1][1] = scale;
        rows[2][2] = scale;
        rows[3][3] = scale;
    }

    mat4() {}
};

struct Vertex {
    // position
    vec3 Position;
    // texCoords
    vec2 TexCoords;

    Vertex(vec3 aPosition, vec2 aTexCoords)
        : Position(aPosition)
        , TexCoords(aTexCoords){};
};

} // namespace ef
