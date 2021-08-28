//
//  Shader.h
//  Neverland
//
//  Created by Admin on 12.07.2021.
//

#include <iostream>

#include "Texture.hpp"
#include "bgfx_utils.hpp"
#include "Shader.hpp"

namespace ef {

Shader::Shader(const char *vertexPath, const char *fragmentPath)
    : m_handle(loadProgram(vertexPath, fragmentPath)) {}

Shader::~Shader() {
    for (auto &item : m_uniformLocationCache) {
        bgfx::destroy(item.second);
    }
    bgfx::destroy(m_handle);
}

bgfx::ProgramHandle Shader::getHandle() {
    return m_handle;
}

void Shader::setTexture(uint8_t number, const std::string &name, Texture &texture) {
    bgfx::setTexture(number, getUniformLocation(name, bgfx::UniformType::Sampler), texture.getHandle());
}

void Shader::setVec4(const std::string &name, const float *mat) {
    bgfx::setUniform(getUniformLocation(name, bgfx::UniformType::Vec4), mat);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    float vec4[4] = {x, y, z, w};
    setVec4(name, &vec4[0]);
}

void Shader::setMat3(const std::string &name, const float *mat) {
    bgfx::setUniform(getUniformLocation(name, bgfx::UniformType::Mat3), mat);
}

void Shader::setMat4(const std::string &name, const float *mat) {
    bgfx::setUniform(getUniformLocation(name, bgfx::UniformType::Mat4), mat);
}

bgfx::UniformHandle Shader::getUniformLocation(const std::string &name, const bgfx::UniformType::Enum type) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }
    bgfx::UniformHandle location = bgfx::createUniform(name.c_str(), type);
    if (bgfx::isValid(location) == false) {
        std::cout << "WARNING:SHADER:UNIFORM " << name << " not found" << std::endl;
    }
    m_uniformLocationCache[name] = location;
    return location;
}

} // namespace ef
