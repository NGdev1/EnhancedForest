//
//  VertexBuffer.hpp
//  Neverland
//
//  Created by Admin on 14.07.2021.
//

#pragma once

#include "Common.h"

#include <bgfx/bgfx.h>

class VertexBuffer {
private:
    bgfx::VertexBufferHandle m_handle;

public:
    VertexBuffer(Vertex *vertices, unsigned int verticesCount);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};
