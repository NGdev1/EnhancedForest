//
//  CoreMesh.hpp
//  Neverland
//
//  Created by Admin on 13.07.2021.
//

#pragma once
#include <string>
#include <vector>

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Vertex.h"

namespace ef {

class CoreMesh {
    IndexBuffer ib;
    VertexBuffer vb;
    Shader *shader;
    Texture *texture;

public:
    CoreMesh(Vertex *vertices, int verticesCount, uint16_t *indices, int indicesCount, Texture *texutre, Shader *shader);
    ~CoreMesh();
    void draw();
};

} // namespace ef
