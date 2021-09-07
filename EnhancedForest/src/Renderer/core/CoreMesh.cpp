//
//  CoreMesh.cpp
//  Neverland
//
//  Created by Admin on 13.07.2021.
//

#include <iostream>
#include <bgfx/bgfx.h>

#include "CoreMesh.hpp"

namespace ef {

CoreMesh::CoreMesh(ef::Vertex *vertices, int verticesCount, uint16_t *indices, int indicesCount, Texture *texture, Shader *shader)
    : vb(vertices, verticesCount)
    , ib(indices, indicesCount)
    , texture(texture)
    , shader(shader) {}

CoreMesh::~CoreMesh() {
    delete texture;
    delete shader;
}

void CoreMesh::draw() {
    shader->setTexture(0, "s_texColor", *texture);
    vb.bind();
    ib.bind();
    bgfx::setState(BGFX_STATE_DEFAULT);
    bgfx::submit(0, shader->getHandle());
}

} // namespace ef
