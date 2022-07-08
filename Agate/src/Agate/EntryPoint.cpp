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
    click.SetCallBackFunc(std::bind(&EntryPoint::eventTest, this, std::placeholders::_1));
    auto search = EventNotifier(click);

    while (1)
    {
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    PRINTWARN("EVENTTEST");
}
