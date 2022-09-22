//
// Created by TANK1_41 on 9/12/2022.
//

#ifndef AGATE_SHADER_H
#define AGATE_SHADER_H
#include <glm/glm.hpp>

namespace Agate
{

    class Shader {

    public:
        Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
        virtual ~Shader();


        void Bind();
        void UnBind();

        void SetUniform4f(const char *uniform, float x, float y, float z, float w);
        void SetUniform3f(const char *uniform, float x, float y, float z);
        void SetUniformMat4(const char *uniform, glm::mat4 trans);
        void SetUniform1i(const char *uniform, int value);

    private:
        int getUniformLoc(const char *uniform) const;
        void shaderCompileStatus(unsigned int id);

        int m_shaderProgramID;
        unsigned int m_fragmentShaderID;
        unsigned int m_vertexShaderID;
    };


}// namespace Agate

#endif//AGATE_SHADER_H
