//
//  Texture.hpp
//  Neverland
//
//  Created by Admin on 20.07.2021.
//

#pragma once

#include <string>
#include <bgfx/bgfx.h>

namespace ef {

class Texture {
private:
    bgfx::TextureHandle m_handle;

public:
    Texture(const std::string &path);
    ~Texture();

    bgfx::TextureHandle getHandle();
};

} // namespace ef
