//
// Created by TANK1_41 on 9/6/2022.
//
#include "agpch.h"

#include "Agate/Core/Logger.h"
#include "Context.h"
#include "CurrentContext.h"
#include "Rendering/OpenGl/Render.h"
#include "Rendering/OpenGl/OpenGLCheck.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Agate {
    void OpenGL::CreateContext() {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            PRINTCRIT("GLAD failed to init");
            throw -1;
        } else {
            Agate::CurrentContext::SetContextPointer((Context *) this);
        }
        GLCall(glEnable(GL_DEPTH_TEST));
    }

    void OpenGL::EndContext() {
    }

    void OpenGL::NewFrame() {
        GLCall(glClearColor(0.2, 0.2, 0.2, 1));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        Render::framesRendered++;
    }

    void OpenGL::SetWindowSize(int width, int height) {
        GLCall(glViewport(0, 0, width, height));
    }
}// namespace Agate