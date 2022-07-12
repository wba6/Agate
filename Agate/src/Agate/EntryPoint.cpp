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
    auto click = MouseClick(50, 50);
    eventTest(click);

    while (1)
    {
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<MouseClick>(std::bind(&EntryPoint::OnMouseClick, this, std::placeholders::_1));

    PRINTMSG("Event Type is:");
    e.PrintEventName();
    e.Handled();
}

bool Agate::EntryPoint::OnMouseClick(MouseClick &e)
{
    PRINTMSG("Event Type is:");
    e.PrintEventName();

    return true;
}
