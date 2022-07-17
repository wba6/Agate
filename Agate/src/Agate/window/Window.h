#pragma once

namespace Agate
{
    class Window {
        Window(std::string WindowName, int size_x, int size_y);


        void SetWindowEventCallbackFn();

    private:
        struct WindowProperies {
            std::string name;
            int width, height;
        };
        WindowProperies windowProps;
    };
}// namespace Agate
