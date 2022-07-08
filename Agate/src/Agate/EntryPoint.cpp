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
    using EventFn = std::function<void()>;
    EventFn func = std::bind(&EntryPoint::eventTest, this);
    click.SetCallBackFunc(func);
    auto search = EventNotifier(click);

    while (1)
    {
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest()
{
    PRINTWARN("EVENTTEST");
}
