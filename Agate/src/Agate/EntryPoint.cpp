#include "agpch.h"


#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Logger.h"
#include "Math/Math.h"


Agate::EntryPoint::EntryPoint()
{
    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::eventTest), 1);
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
        m_window->OnUpdate();
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<MouseButtonPressed>(BindFn(EntryPoint::OnMousePressed));
    notifier.NotifyEvent<MouseButtonReleased>(BindFn(EntryPoint::OnMouseReleased));

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
