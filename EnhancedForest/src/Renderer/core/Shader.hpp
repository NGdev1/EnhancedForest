//
//  Shader.h
//  Neverland
//
//  Created by Admin on 12.07.2021.
//

#pragma once

#include <string>
#include <unordered_map>
#include <bx/bx.h>

class Shader {
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();
    bgfx::ProgramHandle getHandle();
    void setTexture(uint8_t number, const std::string &name, Texture &texture);
    void setVec4(const std::string &name, const float *mat);
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat3(const std::string &name, const float *mat);
    void setMat4(const std::string &name, const float *mat);

private:
    bgfx::ProgramHandle m_handle;
    std::unordered_map<std::string, bgfx::UniformHandle> m_uniformLocationCache;
    bgfx::UniformHandle getUniformLocation(const std::string &name, const bgfx::UniformType::Enum type);
};
