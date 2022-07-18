#include "agpch.h"


#include "Window.h"
#include <GLFW/glfw3.h>
namespace Agate
{


    Window::Window(std::string WindowName, int size_x, int size_y)
        : windowProps{WindowName, size_x, size_y}
    {
    }

    void Window::InitWindow()
    {
    }
    void Window::OnUpdate()
    {
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
