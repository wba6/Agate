#include "ShaderUser.hpp"
#include "Rendering/Renderer.hpp"

namespace Agate {

    ShaderUser::ShaderUser(const char *vertexShaderPath, const char *fragmentShaderPath)
        : m_vertexShaderPath(vertexShaderPath), m_fragmentShaderPath(fragmentShaderPath) {
        Renderer::Submit(std::make_unique<CreateShader>(*this));
    }

    void ShaderUser::Bind() const {
        Renderer::Submit(std::make_unique<BindShader>(m_UUID));
    }

    void ShaderUser::UnBind() const {
        Renderer::Submit(std::make_unique<UnBindShader>());
    }

    void ShaderUser::SetUniform4f(const char *uniform, float x, float y, float z, float w) {
        Renderer::Submit(std::make_unique<UpdateShaderUniform4f>(m_UUID, uniform, x, y, z, w));
    }

    void ShaderUser::SetUniform3f(const char *uniform, float x, float y, float z) {
        Renderer::Submit(std::make_unique<UpdateShaderUniform3f>(m_UUID, uniform, x, y, z));
    }

    void ShaderUser::SetUniformMat4(const char *uniform, glm::mat4 trans) {
        Renderer::Submit(std::make_unique<UpdateShaderUniformMat4>(m_UUID, uniform, trans));
    }

    void ShaderUser::SetUniform1i(const char *uniform, int value) {
        Renderer::Submit(std::make_unique<UpdateShaderUniform1i>(m_UUID, uniform, value));
    }

    void ShaderUser::SetUniform1f(const char *uniform, float x) {
        Renderer::Submit(std::make_unique<UpdateShaderUniform1f>(m_UUID, uniform, x));
    }

    ShaderUser::~ShaderUser() {
        Renderer::Submit(std::make_unique<DeleteShader>(m_UUID));
    }

}
