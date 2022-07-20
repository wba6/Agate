#pragma once
#include "Core.h"
#include "Events/ApplicationEvents.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "window/Window.h"

namespace Agate
{
    class API EntryPoint {
    public:
        EntryPoint();
        virtual ~EntryPoint();

        void Run();
        void eventTest(Event &e);

        bool OnWindowClose(WindowCloseEvent &e);

    private:
        std::shared_ptr<Window> m_window;
        bool m_running;
    };

}// namespace Agate
