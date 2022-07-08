#pragma once
#include "Core.h"


namespace Agate
{
    class API EntryPoint {
    public:
        EntryPoint();
        virtual ~EntryPoint();

        void Run();
        bool eventTest();
    };

}// namespace Agate
