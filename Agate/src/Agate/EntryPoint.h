#pragma once
#include "Events/Event.h"
#include "Core.h"


namespace Agate
{
    class API EntryPoint {
    public:
        EntryPoint();
        virtual ~EntryPoint();

        void Run();
        void eventTest(Event &e);
    };

}// namespace Agate
