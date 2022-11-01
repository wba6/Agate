#include "agpch.h"

#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvent.h"
#include "Window.h"
#include "RenderContext/Context.h"
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

        m_windowProps.context = new OpenGL;
        m_windowProps.context->CreateContext();

        glfwSetWindowUserPointer(m_Window, &m_windowProps);


        SetVSync(true);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            //need this bc lambda can't access non-static class members
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.callback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xpos, double ypos) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            MouseMoved event((int) xpos, (int) ypos);
            data.callback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            MouseButtonPressed event((int) button);
            data.callback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS)
            {
                KeyPressedEvent event(key);
                data.callback(event);
            }
            else
            {
                KeyReleasedEvent event(key);
                data.callback(event);
            }
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            WindowResizedEvent event(width, height);
            data.callback(event);

            data.context->SetWindowSize(width, height);
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

    void Window::SetVSync(bool enable)
    {
        if (enable)
        {
            glfwSwapInterval(1);
            m_windowProps.VSyncState = true;
        }
        else
        {
            glfwSwapInterval(0);
            m_windowProps.VSyncState = false;
        }
    }

    bool Window::GetVSyncState()
    {
        return m_windowProps.VSyncState;
    }
    GLFWwindow *Window::GetWindow()
    {
        return m_Window;
    }
    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        delete m_windowProps.context;
    }
    double Window::WindowOpenTime()
    {
        return glfwGetTime();
    }


}// namespace Agate
