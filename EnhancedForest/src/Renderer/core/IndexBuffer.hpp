//
//  IndexBuffer.hpp
//  Neverland
//
//  Created by Admin on 15.07.2021.
//

#pragma once

#include <bgfx/bgfx.h>

class IndexBuffer {
private:
    bgfx::IndexBufferHandle m_handle;
    unsigned int m_size;

public:
    IndexBuffer(uint16_t *data, int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    unsigned int getSize() const;
};
