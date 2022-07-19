#pragma once
#include "Core.h"
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

        //temporary for testing--------------------------

        bool OnMousePressed(MouseButtonPressed &e);
        bool OnMouseReleased(MouseButtonReleased &e);

        //-------------------------------------------------
    private:
        std::shared_ptr<Window> m_window;
    };

}// namespace Agate
