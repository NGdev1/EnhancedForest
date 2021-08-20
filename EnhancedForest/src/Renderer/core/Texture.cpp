//
//  Texture.cpp
//  Neverland
//
//  Created by Admin on 20.07.2021.
//

#include "Texture.hpp"
#include "bgfx_utils.hpp"

Texture::Texture(const std::string &path)
    : m_handle(loadTexture(path.c_str())) {}

Texture::~Texture() {
    bgfx::destroy(m_handle);
}

bgfx::TextureHandle Texture::getHandle() {
    return m_handle;
}
