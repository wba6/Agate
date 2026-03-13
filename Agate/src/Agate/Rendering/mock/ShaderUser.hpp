#ifndef AGATE_SHADERUSER_HPP
#define AGATE_SHADERUSER_HPP

#include <string>
#include <glm/glm.hpp>
#include "Rendering/UUID.hpp"

namespace Agate {

    class ShaderUser {

    public:
        ShaderUser(const char *vertexShaderPath, const char *fragmentShaderPath)
            : m_vertexShaderPath(vertexShaderPath), m_fragmentShaderPath(fragmentShaderPath) {}

        virtual ~ShaderUser() = default;

        const std::string& getVertexShaderPath() const { return m_vertexShaderPath; }
        const std::string& getFragmentShaderPath() const { return m_fragmentShaderPath; }
        UUID getUUID() const { return m_UUID; }

        void SetUniform4f(const char *uniform, float x, float y, float z, float w);
        void SetUniform3f(const char *uniform, float x, float y, float z);
        void SetUniformMat4(const char *uniform, glm::mat4 trans);
        void SetUniform1i(const char *uniform, int value);
        void SetUniform1f(const char *uniform, float x);

    private:
        std::string m_vertexShaderPath;
        std::string m_fragmentShaderPath;
        UUID m_UUID;
    };


}// namespace Agate

#endif//AGATE_SHADERUSER_HPP
