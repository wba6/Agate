#pragma once
#include "Events/Event.h"


namespace Agate
{

    class Window {

    public:
        using EventCallbackFn = std::function<void(Event &)>;
        Window(std::string WindowName, int size_x, int size_y);


        void OnUpdate();

        void GetWidth();
        void GetHieght();
        void SetVSync();
        void GetVSyncState();

    private:
        void InitWindow();

        struct WindowProperies {
            std::string name;
            int width, height;
            bool VSyncState;
            EventCallbackFn callback;
        };


        WindowProperies windowProps;
    };
}// namespace Agate
