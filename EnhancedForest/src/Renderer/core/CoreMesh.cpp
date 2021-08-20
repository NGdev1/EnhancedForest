//
//  CoreMesh.cpp
//  Neverland
//
//  Created by Admin on 13.07.2021.
//

#include <iostream>
#include <bgfx/bgfx.h>

#include "CoreMesh.hpp"

CoreMesh::CoreMesh(
    Vertex *vertices, int verticesCount, uint16_t *indices, int indicesCount, std::vector<Texture *> textures, Shader *shader)
    : vb(vertices, verticesCount)
    , ib(indices, indicesCount)
    , textures(textures)
    , shader(shader) {}

CoreMesh::~CoreMesh() {}

void CoreMesh::draw() {
    for (int i = 0; i < textures.size(); i++) {
        Texture *&texture = textures[i];
        shader->setTexture(i, "s_texColor", *texture);
    }
    vb.bind();
    ib.bind();
    bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::submit(0, shader->getHandle());
}
