#pragma once
#include "Events/Event.h"


typedef struct GLFWwindow;
namespace Agate
{
    class Window {

    public:
        using EventCallbackFn = std::function<void(Event &)>;
        Window(std::string WindowName, int size_x, int size_y, EventCallbackFn callback, bool vsync);


        void OnUpdate();

        void GetWidth();
        void GetHieght();
        void SetVSync();
        void GetVSyncState();

    private:
        void InitWindow();
        static void GlfwError(int error_code, const char *description);

        struct WindowProperies {
            std::string name;
            int width, height;
            EventCallbackFn callback;
            bool VSyncState;
        };

        GLFWwindow *m_Window;

        WindowProperies windowProps;
    };
}// namespace Agate
