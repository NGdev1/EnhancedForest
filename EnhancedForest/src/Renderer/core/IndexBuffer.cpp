//
//  IndexBuffer.cpp
//  Neverland
//
//  Created by Admin on 15.07.2021.
//

#include "IndexBuffer.hpp"

namespace ef {

IndexBuffer::IndexBuffer(uint16_t *data, int count)
    : m_size(count)
    , m_handle(bgfx::createIndexBuffer(bgfx::makeRef(data, sizeof(uint16_t) * count))) {}

IndexBuffer::~IndexBuffer() {
    bgfx::destroy(m_handle);
}

void IndexBuffer::bind() const {
    bgfx::setIndexBuffer(m_handle);
}

void IndexBuffer::unbind() const {
    bgfx::setIndexBuffer(0);
}

unsigned int IndexBuffer::getSize() const {
    return m_size;
}

} // namespace ef
