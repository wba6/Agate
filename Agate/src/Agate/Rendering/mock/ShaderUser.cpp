#include "ShaderUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    ShaderUser::ShaderUser(const char *vertexShaderPath, const char *fragmentShaderPath)
    : m_vertexShaderPath(vertexShaderPath), m_fragmentShaderPath(fragmentShaderPath), m_UUID(UUID::Generate()) {
        Renderer::Submit(std::make_unique<CreateShader>(*this));
    }

    ShaderUser::ShaderUser(ShaderUser&& other) noexcept
    : m_vertexShaderPath(std::move(other.m_vertexShaderPath)), m_fragmentShaderPath(std::move(other.m_fragmentShaderPath)), m_UUID(other.m_UUID) {
        other.m_UUID = UUID();
    }

    ShaderUser& ShaderUser::operator=(ShaderUser&& other) noexcept {
        if (this != &other) {
            // If this object already manages a resource, delete it
            if (m_UUID) {
                Renderer::Submit(std::make_unique<DeleteShader>(m_UUID));
            }

            m_vertexShaderPath = std::move(other.m_vertexShaderPath);
            m_fragmentShaderPath = std::move(other.m_fragmentShaderPath);
            m_UUID = other.m_UUID;

            other.m_UUID = UUID();
        }
        return *this;
    }

    void ShaderUser::Bind() const {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<BindShader>(m_UUID));
        }
    }

    void ShaderUser::UnBind() const {
        Renderer::Submit(std::make_unique<UnBindShader>());
    }

    void ShaderUser::SetUniform4f(const char *uniform, float x, float y, float z, float w) {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<UpdateShaderUniform4f>(m_UUID, uniform, x, y, z, w));
        }
    }

    void ShaderUser::SetUniform3f(const char *uniform, float x, float y, float z) {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<UpdateShaderUniform3f>(m_UUID, uniform, x, y, z));
        }
    }

    void ShaderUser::SetUniformMat4(const char *uniform, glm::mat4 trans) {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<UpdateShaderUniformMat4>(m_UUID, uniform, trans));
        }
    }

    void ShaderUser::SetUniform1i(const char *uniform, int value) {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<UpdateShaderUniform1i>(m_UUID, uniform, value));
        }
    }

    void ShaderUser::SetUniform1f(const char *uniform, float x) {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<UpdateShaderUniform1f>(m_UUID, uniform, x));
        }
    }

    ShaderUser::~ShaderUser() {
        if (m_UUID) {
            Renderer::Submit(std::make_unique<DeleteShader>(m_UUID));
        }
    }

}
