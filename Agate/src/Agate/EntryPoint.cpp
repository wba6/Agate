#include "agpch.h"

#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Math/Math.h"
#include "imgui-layer/imguiLayer.h"
#include <glad/glad.h>
Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;

Agate::EntryPoint::EntryPoint()
{
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::OnEvent), true);
    m_running = true;

    m_layerStack.AddOverlay(new imguiLayer(m_window->GetWindow()));
}

Agate::EntryPoint::~EntryPoint()
{
}

void Agate::EntryPoint::Run()
{
//    auto click = MouseButtonPressed(0);
//    OnEvent(click);
//    auto click_r = MouseButtonReleased(0);
//    OnEvent(click_r);

    while (m_running)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        imguiLayer::Begin();
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++)
        {
            m_layerStack.m_layers.at(i)->onRender();
        }
        imguiLayer::End();

        m_window->OnUpdate();

    };
}

void Agate::EntryPoint::OnEvent(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<WindowCloseEvent>(BindFn(EntryPoint::OnWindowClose));

    //PRINTMSG("Event Type is:");
    e.PrintEventName();

    for (size_t i{0}; i < m_layerStack.m_layers.size(); i++)
    {
        m_layerStack.m_layers.at(i)->OnEvent(e);
        if (e.Handled())
            break;
    }
}


bool Agate::EntryPoint::OnWindowClose(WindowCloseEvent &e)
{
    m_running = false;
    return true;
}

void Agate::EntryPoint::EmplaceLayer(Layer *layer)
{
    m_layerStack.AddLayer(layer);
}

void Agate::EntryPoint::RemoveLayer(Layer *layer)
{
    m_layerStack.RemoveLayer(layer);
}

void Agate::EntryPoint::EmplaceOverlay(Layer *overlay)
{
    m_layerStack.AddOverlay(overlay);
}

void Agate::EntryPoint::RemoveOverlay(Layer *overlay)
{
    m_layerStack.RemoveOverlay(overlay);
}
