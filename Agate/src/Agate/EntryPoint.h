#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"

namespace Agate
{
    class API EntryPoint {
    public:
        EntryPoint();
        virtual ~EntryPoint();

        void Run();
        void eventTest(Event &e);
        bool OnMouseClick(MouseClick &e);
    };

}// namespace Agate
