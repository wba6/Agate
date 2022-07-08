#include "EntryPoint.h"
#include "../Events/Event.h"
#include "../Events/MouseEvent.h"
#include "Logger.h"
#include <functional>
Agate::EntryPoint::EntryPoint()
{
}

Agate::EntryPoint::~EntryPoint()
{
}

void Agate::EntryPoint::Run()
{
    auto click = MouseClick();
    auto search = EventNotifier(click);
    MouseClick->SetCallBackFunc(Agate::EntryPoint::eventTest)

            while (1)
    {
        PRINTWARN("Bacon");
    };
}

bool Agate::EntryPoint::eventTest()
{
    PRINTWARN("EVENTTEST");
}
