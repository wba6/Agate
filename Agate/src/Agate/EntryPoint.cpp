#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
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
    auto click = MouseClick(50,50);
    click.SetCallBackFunc(std::bind(&EntryPoint::eventTest, this, std::placeholders::_1));
    auto search = EventNotifier();
    search.NotifyEvent(click);

    auto clickTwo = MouseClick(60, 20);
    search.NotifyEvent(clickTwo);
    
    while (1)
    {
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    PRINTMSG("Event Type is:");
    e.PrintEventName();
}
