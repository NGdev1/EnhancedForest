//
//  Mesh.cpp
//  Neverland
//
//  Created by Admin on 13.07.2021.
//

#include <iostream>
#include <bgfx/bgfx.h>

#include "Mesh.hpp"

Mesh::Mesh(Vertex *vertices, unsigned int verticesCount, unsigned int *indices, unsigned int indicesCount, std::vector<Texture *> textures,
    Shader &shader)
    : ib(indices, indicesCount)
    , vb(vertices, verticesCount)
    , textures(textures)
    , shader(shader) {}

Mesh::~Mesh() {}

void Mesh::draw() {
    ib.bind();
    vb.bind();
    bgfx::submit(0, shader.getHandle());
}
