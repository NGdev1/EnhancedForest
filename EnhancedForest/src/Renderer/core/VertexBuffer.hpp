//
//  VertexBuffer.hpp
//  Neverland
//
//  Created by Admin on 14.07.2021.
//

#pragma once

#include "Vertex.h"

#include <bgfx/bgfx.h>

namespace ef {

class VertexBuffer {
private:
    bgfx::VertexBufferHandle m_handle;

public:
    VertexBuffer(Vertex *vertices, int verticesCount);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

} // namespace ef
