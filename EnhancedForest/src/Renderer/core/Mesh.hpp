//
//  Mesh.hpp
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

class Mesh {
    IndexBuffer ib;
    VertexBuffer vb;
    Shader shader;
    std::vector<Texture *> textures;

public:
    Mesh(Vertex *vertices, unsigned int verticesCount, unsigned int *indices, unsigned int indicesCount, std::vector<Texture *> texutres,
        Shader &shader);
    ~Mesh();
    void draw();
};
