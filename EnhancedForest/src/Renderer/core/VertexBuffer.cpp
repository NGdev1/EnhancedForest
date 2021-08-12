//
//  VertexBuffer.cpp
//  Neverland
//
//  Created by Admin on 14.07.2021.
//

#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(Vertex *vertices, unsigned int verticesCount) {
    bgfx::VertexLayout layout;
    layout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
    layout.add(bgfx::Attrib::TexCoord0, 4, bgfx::AttribType::Float);

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
