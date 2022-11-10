#pragma once
#include "Agate/Events/Event.h"

//TODO: Use a bridge and a factor to create this window so that there is only one instance so the api can be exposed to client


namespace Agate
{
    class Context;
    class Window {

    public:
        using EventCallbackFn = std::function<void(Event &)>;
        Window(std::string WindowName, int size_x, int size_y, EventCallbackFn callback, bool vsync);
        ~Window();

        void OnUpdate();
        double WindowOpenTime();
        int GetWidth();
        int GetHieght();
        void GrabCursor(bool cursor);
        void SetVSync(bool enable);
        bool GetVSyncState();
        void *GetInstanceWindow();

    private:
        void InitWindow();
        static void GlfwError(int error_code, const char *description);

        struct WindowProperies {
            std::string name;
            int width, height;
            EventCallbackFn callback;
            bool VSyncState;
            Context *context;
        };
        void *m_Window;

        WindowProperies m_windowProps;
    };
}// namespace Agate
