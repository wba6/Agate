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
    auto click = MouseButtonPressed(1);
    eventTest(click);

    while (1)
    {
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<MouseButtonPressed>(std::bind(&EntryPoint::OnMouseClick, this, std::placeholders::_1));

    PRINTMSG("Event Type is:");
    e.PrintEventName();
}


//temporary for testing----------------------------------------------
bool Agate::EntryPoint::OnMouseClick(MouseButtonPressed &e)
{
    PRINTMSG("Event Type is:");
    e.PrintEventName();

    return true;
}
//temporary for testing----------------------------------------------
