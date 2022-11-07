//
// Created by TANK1_41 on 9/6/2022.
//
#include "agpch.h"

#include "Agate/Core/Logger.h"
#include "Context.h"
#include "CurrentContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
namespace Agate
{
    void OpenGL::CreateContext()
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            PRINTCRIT("GLAD failed to init");
            throw -1;
        }
        else
        {
            Agate::CurrentContext::SetContextPointer((Context *) this);
        }
    }
    void OpenGL::EndContext()
    {
    }
    void OpenGL::NewFrame()
    {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void OpenGL::SetWindowSize(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}// namespace Agate