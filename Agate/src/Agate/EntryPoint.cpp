#include "agpch.h"


#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Logger.h"
#include "Math/Vect.h"

Agate::EntryPoint::EntryPoint()
{
}

Agate::EntryPoint::~EntryPoint()
{
}

void Agate::EntryPoint::Run()
{
    auto click = MouseButtonPressed(0);
    eventTest(click);
    auto click_r = MouseButtonReleased(0);
    eventTest(click_r);

    while (1)
    {
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<MouseButtonPressed>(std::bind(&EntryPoint::OnMousePressed, this, std::placeholders::_1));
    notifier.NotifyEvent<MouseButtonReleased>(std::bind(&EntryPoint::OnMouseReleased, this, std::placeholders::_1));

    PRINTMSG("Event Type is:");
    e.PrintEventName();
}


//temporary for testing----------------------------------------------
bool Agate::EntryPoint::OnMousePressed(MouseButtonPressed &e)
{
    PRINTMSG("Event Type is:");
    e.PrintEventName();

    return true;
}
//temporary for testing----------------------------------------------
//temporary for testing----------------------------------------------
bool Agate::EntryPoint::OnMouseReleased(MouseButtonReleased &e)
{
    PRINTMSG("Event Type is:");
    e.PrintEventName();

    return true;
}
//temporary for testing----------------------------------------------
