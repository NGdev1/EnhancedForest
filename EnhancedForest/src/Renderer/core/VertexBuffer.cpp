//
//  VertexBuffer.cpp
//  Neverland
//
//  Created by Admin on 14.07.2021.
//

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(Vertex *vertices, int verticesCount) {
    bgfx::VertexLayout layout;
    layout.begin();
    layout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
    layout.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
    layout.end();

    int size = sizeof(Vertex) * verticesCount;
    m_handle = bgfx::createVertexBuffer(bgfx::makeRef(vertices, size), layout);
}

VertexBuffer::~VertexBuffer() {
    bgfx::destroy(m_handle);
}

void VertexBuffer::bind() const {
    bgfx::setVertexBuffer(0, m_handle);
}

void VertexBuffer::unbind() const {
    bgfx::setVertexBuffer(0, 0);
}
