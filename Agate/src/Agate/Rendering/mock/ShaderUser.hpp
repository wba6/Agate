#ifndef AGATE_SHADERUSER_HPP
#define AGATE_SHADERUSER_HPP

#include <string>
#include <glm/glm.hpp>
#include "Agate/Rendering/UUID.hpp"

namespace Agate {

    /**
     * @brief A mock representation of an OpenGL Shader for use on the main thread.
     *
     * ShaderUser stores shader source paths and associated metadata (UUIDs)
     * to allow the application to interact with shaders without
     * directly making OpenGL calls.
     */
    class ShaderUser {

    public:
        /**
         * @brief Constructs a ShaderUser.
         *
         * @param vertexShaderPath The path to the vertex shader source.
         * @param fragmentShaderPath The path to the fragment shader source.
         */
        ShaderUser(const char *vertexShaderPath, const char *fragmentShaderPath);

        // Disable copying
        ShaderUser(const ShaderUser&) = delete;
        ShaderUser& operator=(const ShaderUser&) = delete;

        // Enable move semantics
        ShaderUser(ShaderUser&& other) noexcept;
        ShaderUser& operator=(ShaderUser&& other) noexcept;

        /**
         * @brief Virtual destructor for ShaderUser.
         */
        virtual ~ShaderUser();

        /**
         * @brief Gets the path to the vertex shader source.
         * @return The vertex shader path.
         */
        const std::string& getVertexShaderPath() const { return m_vertexShaderPath; }

        /**
         * @brief Gets the path to the fragment shader source.
         * @return The fragment shader path.
         */
        const std::string& getFragmentShaderPath() const { return m_fragmentShaderPath; }

        /**
         * @brief Gets the UUID of this Shader.
         * @return The UUID of the shader.
         */
        UUID getUUID() const { return m_UUID; }

        /**
         * @brief Binds the shader.
         *
         * Enqueues a command to bind the underlying OpenGL shader.
         */
        void Bind() const;

        /**
         * @brief Unbinds the shader.
         *
         * Enqueues a command to unbind the underlying OpenGL shader.
         */
        void UnBind() const;

        /**
         * @brief Sets a 4f uniform.
         * @param uniform The name of the uniform.
         * @param x, y, z, w The values for the uniform.
         */
        void SetUniform4f(const char *uniform, float x, float y, float z, float w);

        /**
         * @brief Sets a 3f uniform.
         * @param uniform The name of the uniform.
         * @param x, y, z The values for the uniform.
         */
        void SetUniform3f(const char *uniform, float x, float y, float z);

        /**
         * @brief Sets a mat4 uniform.
         * @param uniform The name of the uniform.
         * @param trans The matrix value for the uniform.
         */
        void SetUniformMat4(const char *uniform, glm::mat4 trans);

        /**
         * @brief Sets a 1i uniform.
         * @param uniform The name of the uniform.
         * @param value The value for the uniform.
         */
        void SetUniform1i(const char *uniform, int value);

        /**
         * @brief Sets a 1f uniform.
         * @param uniform The name of the uniform.
         * @param x The value for the uniform.
         */
        void SetUniform1f(const char *uniform, float x);

    private:
        std::string m_vertexShaderPath;
        std::string m_fragmentShaderPath;
        UUID m_UUID;
    };


}// namespace Agate

#endif//AGATE_SHADERUSER_HPP
