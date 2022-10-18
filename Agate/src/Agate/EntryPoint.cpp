#include "agpch.h"

#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Math/Math.h"
#include "RenderContext/CurrentContext.h"
#include "ImGui-layer/imguiLayer.h"
//TODO: TEMPORARY include
#include "Agate/Rendering/temp_test_layer.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;

Agate::EntryPoint::EntryPoint()
{
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::OnEvent), true);
    m_running = true;

    m_layerStack.AddOverlay(new imguiLayer(m_window->GetWindow()));
    CurrentContext::OpenGL = true;
}

Agate::EntryPoint::~EntryPoint()
{
}

void Agate::EntryPoint::Run()
{

    while (m_running)
    {
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        imguiLayer::Begin();
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++)
        {
            m_layerStack.m_layers.at(i)->OnRender();
        }
        imguiLayer::End();

        m_window->OnUpdate();
    };
}

void Agate::EntryPoint::OnEvent(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<WindowCloseEvent>(BindFn(EntryPoint::OnWindowClose));


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
Agate::EntryPoint *&Agate::EntryPoint::GetInstance()
{
    return s_instance;
}
