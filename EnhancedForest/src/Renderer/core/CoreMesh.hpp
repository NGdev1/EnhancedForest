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
#include "Common.h"

class CoreMesh {
    IndexBuffer ib;
    VertexBuffer vb;
    Shader *shader;
    std::vector<Texture *> textures;

public:
    CoreMesh(Vertex *vertices, int verticesCount, uint16_t *indices, int indicesCount, std::vector<Texture *> texutres, Shader *shader);
    ~CoreMesh();
    void draw();
};
