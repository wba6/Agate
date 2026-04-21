#include "agpch.h"

#include "Events/ApplicationEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvent.h"
#include "RenderContext/Context.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <stdexcept>


namespace Agate {


    Window::Window(std::string WindowName, int size_x, int size_y, EventCallbackFn callback, bool vsync)
            : m_windowProps(std::move(WindowName), size_x, size_y, std::move(callback), vsync) {
        InitWindow();
    }

    void Window::InitWindow() {
        if (!glfwInit())
            PRINTCRIT("GLFW FAILED INIT-------------------");
        glfwSetErrorCallback(GlfwError);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // MacOS supports up to 4.1, but 3.3 is safer common ground
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Required on Mac
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);            // Required on Mac

        m_Window = glfwCreateWindow(m_windowProps.width.load(), m_windowProps.height.load(), m_windowProps.name.c_str(), nullptr,
                                    nullptr);
        glfwMakeContextCurrent((GLFWwindow *) m_Window);

        m_windowProps.context = new OpenGL;
        m_windowProps.context->CreateContext();

        glfwSetWindowUserPointer((GLFWwindow *) m_Window, &m_windowProps);
        glfwSetInputMode((GLFWwindow *) m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        SetVSync(true);

        glfwSetWindowCloseCallback((GLFWwindow *) m_Window, [](GLFWwindow *window) {
            //need this bc lambda can't access non-static class members
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.callback(event);
        });

        glfwSetCursorPosCallback((GLFWwindow *) m_Window, [](GLFWwindow *window, double xpos, double ypos) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            MouseMoved event((int) xpos, (int) ypos);
            data.callback(event);
        });

        glfwSetMouseButtonCallback((GLFWwindow *) m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            MouseButtonPressed event((int) button);
            data.callback(event);
        });

        glfwSetKeyCallback((GLFWwindow *) m_Window,
                           [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                               WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

                               if (action == GLFW_PRESS) {
                                   KeyPressedEvent event(key);
                                   data.callback(event);
                               } else {
                                   KeyReleasedEvent event(key);
                                   data.callback(event);
                               }
                           });

        glfwSetWindowSizeCallback((GLFWwindow *) m_Window, [](GLFWwindow *window, int width, int height) {
            WindowProperies &data = *(WindowProperies *) glfwGetWindowUserPointer(window);

            WindowResizedEvent event(width, height);
            data.width.store(width);
            data.height.store(height);
            data.callback(event);
        });
    }

    void Window::GlfwError(int error_code, const char *description) {
        PRINTCRIT("GLFW ERROR---CODE: {} : {}", error_code, description);
    }

    void Window::SwapBuffers() {
        std::lock_guard<std::recursive_mutex> lock(m_SyncMutex);
        glfwSwapBuffers((GLFWwindow *) m_Window);
    }

    void Window::PollEvents() {
        std::lock_guard<std::recursive_mutex> lock(m_SyncMutex);
        glfwPollEvents();
    }

    int Window::GetWidth() {
        return m_windowProps.width.load();
    }

    int Window::GetHieght() {
        return m_windowProps.height.load();
    }

    void Window::SetVSync(bool enable) {
        std::lock_guard<std::recursive_mutex> lock(m_SyncMutex);
        if (enable) {
            glfwSwapInterval(1);
            m_windowProps.VSyncState.store(true);
        } else {
            glfwSwapInterval(0);
            m_windowProps.VSyncState.store(false);
        }
    }

    bool Window::GetVSyncState() {
        return m_windowProps.VSyncState.load();
    }

    void *Window::GetInstanceWindow() {
        return m_Window;
    }

    Window::~Window() {
        glfwDestroyWindow((GLFWwindow *) m_Window);
        delete m_windowProps.context;
    }

    double Window::WindowOpenTime() {
        return glfwGetTime();
    }

    void Window::GrabCursor(bool cursor) {
        std::lock_guard<std::recursive_mutex> lock(m_SyncMutex);
        if (cursor) {
            glfwSetInputMode((GLFWwindow *) m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode((GLFWwindow *) m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void Window::AttachContext() {
        std::lock_guard<std::recursive_mutex> lock(m_SyncMutex);
        glfwMakeContextCurrent((GLFWwindow *)m_Window);
    }

    void Window::DetachContext() {
        std::lock_guard<std::recursive_mutex> lock(m_SyncMutex);
        glfwMakeContextCurrent(NULL);
    }

    void Window::SetSizeLimits(int minWidth, int minHeight, int maxWidth, int maxHeight) {

        if (minWidth > maxWidth || minHeight > maxHeight) {
            throw std::invalid_argument("Invalid size limits");
        }

        if (minWidth <= 0 || minHeight <= 0 || maxWidth <= 0 || maxHeight <= 0) {
            throw std::invalid_argument("1 or more dimensions below 0");
        }

        int width = std::clamp(m_windowProps.width.load(), minWidth, maxWidth);
        int height = std::clamp(m_windowProps.height.load(), minHeight, maxHeight);
        if (width != m_windowProps.width || height != m_windowProps.height) {
            glfwSetWindowSize((GLFWwindow*) m_Window, width, height);
        }

        glfwSetWindowSizeLimits(
            (GLFWwindow*) m_Window,
            minWidth,
            minHeight,
            maxWidth,
            maxHeight
        );
    }

    void Window::SetMinimumSize(int minWidth, int minHeight) {

        if (minWidth <= 0 || minHeight <= 0) {
            throw std::invalid_argument("1 or more dimensions 0 or less");
        }

        int contentWidth;
        int contentHeight;
        glfwGetWindowSize(
            static_cast<GLFWwindow*>(m_Window),
            &contentWidth,
            &contentHeight
        );

        if (minWidth > contentWidth || minHeight > contentHeight) {
            glfwSetWindowSize(static_cast<GLFWwindow*>(m_Window), minWidth, minHeight);
        }

        glfwSetWindowSizeLimits(
            static_cast<GLFWwindow*>(m_Window),
            minWidth,
            minHeight,
            GLFW_DONT_CARE,
            GLFW_DONT_CARE
        );
    }

    void Window::RemoveSizeLimits() {

        glfwSetWindowSizeLimits(
            (GLFWwindow*) m_Window,
            GLFW_DONT_CARE,
            GLFW_DONT_CARE,
            GLFW_DONT_CARE,
            GLFW_DONT_CARE
        );
    }

}// namespace Agate
