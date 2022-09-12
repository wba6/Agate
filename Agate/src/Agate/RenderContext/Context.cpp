//
// Created by TANK1_41 on 9/6/2022.
//
#include "agpch.h"

#include "Context.h"
#include "Logger.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
namespace Agate
{
    void OpenGL::CreateContext()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            PRINTCRIT("GLAD failed to init");
            throw -1;
        }
    }
    void OpenGL::EndContext()
    {
    }
}// namespace Agate