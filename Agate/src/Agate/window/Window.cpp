#include "agpch.h"

#include "Events/ApplicationEvents.h"
#include "Events/MouseEvent.h"
#include "Window.h"
#include <GLFW/glfw3.h>
namespace Agate
{


    Window::Window(std::string WindowName, int size_x, int size_y, EventCallbackFn callback, bool vsync)
        : m_windowProps{WindowName, size_x, size_y, callback, vsync}
    {
        InitWindow();
    }

    void Window::InitWindow()
    {
        if (!glfwInit())
            PRINTCRIT("GLFW FAILED INIT-------------------");
        glfwSetErrorCallback(GlfwError);

        m_Window = glfwCreateWindow(m_windowProps.width, m_windowProps.height, m_windowProps.name.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);

        glfwSetWindowUserPointer(m_Window, &m_windowProps);


        //SetVSync(true);//need glad --------------------------------------------------------------------------------------------------------

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            //need this bc lambda can't access non-static class members
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.callback(event);
        });
    }

    void Window::GlfwError(int error_code, const char *description)
    {
        PRINTCRIT("GLFW ERROR---CODE:" + std::to_string(error_code) + " :" + description);
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::GetWidth()
    {
    }

    void Window::GetHieght()
    {
    }

    void Window::SetVSync()
    {
    }

    void Window::GetVSyncState()
    {
    }


}// namespace Agate
