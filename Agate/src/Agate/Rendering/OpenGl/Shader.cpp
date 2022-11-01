//
// Created by TANK1_41 on 9/12/2022.
//
#include "agpch.h"

#include "Agate/Core/Logger.h"
#include "Shader.h"
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

namespace Agate
{


    Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
    {
        // 1. retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexShaderPath);
            fShaderFile.open(fragmentShaderPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertexShaderID, 1, &vShaderCode, NULL);
        glCompileShader(m_vertexShaderID);
        shaderCompileStatus(m_vertexShaderID);

        m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShaderID, 1, &fShaderCode, NULL);
        glCompileShader(m_fragmentShaderID);
        shaderCompileStatus(m_fragmentShaderID);

        m_shaderProgramID = glCreateProgram();

        glAttachShader(m_shaderProgramID, m_vertexShaderID);
        glAttachShader(m_shaderProgramID, m_fragmentShaderID);
        glLinkProgram(m_shaderProgramID);

        int success;
        char infoLog[512];
        glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_shaderProgramID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }
    }
    void Shader::shaderCompileStatus(unsigned int id)
    {
        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
            PRINTCRIT("m_Shader failed to compile");
        }
    }
    void Shader::Bind()
    {
        glUseProgram(m_shaderProgramID);
    }
    void Shader::UnBind()
    {
        glUseProgram(0);
    }
    Shader::~Shader()
    {
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_vertexShaderID);
    }
    int Shader::getUniformLoc(const char *uniform) const
    {

        int loc = glGetUniformLocation(m_shaderProgramID, uniform);
        if (loc == -1)
            PRINTCRIT("m_Shader not found");
        return loc;
    }
    void Shader::SetUniform4f(const char *uniform, float x, float y, float z, float w)
    {
        glUniform4f(getUniformLoc(uniform), x, y, z, w);
    }
    void Shader::SetUniform1i(const char *uniform, int value)
    {
        glUniform1i(getUniformLoc(uniform), value);
    }
    void Shader::SetUniformMat4(const char *uniform, glm::mat4 trans)
    {
        glUniformMatrix4fv(getUniformLoc(uniform), 1, GL_FALSE, glm::value_ptr(trans));
    }
    void Shader::SetUniform3f(const char *uniform, float x, float y, float z)
    {
        glUniform3f(getUniformLoc(uniform), x, y, z);
    }
}// namespace Agate