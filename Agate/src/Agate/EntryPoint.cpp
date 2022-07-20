#include "agpch.h"


#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Math/Math.h"


Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;

Agate::EntryPoint::EntryPoint()
{
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::eventTest), true);
    m_running = true;
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

    while (m_running)
    {
        m_window->OnUpdate();
        //PRINTWARN("Bacon");
    };
}

void Agate::EntryPoint::eventTest(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<WindowCloseEvent>(BindFn(EntryPoint::OnWindowClose));

    PRINTMSG("Event Type is:");
    e.PrintEventName();
}


bool Agate::EntryPoint::OnWindowClose(WindowCloseEvent &e)
{
    m_running = false;
    return true;
}
