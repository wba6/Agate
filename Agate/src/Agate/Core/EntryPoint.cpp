#include "agpch.h"

#include "EntryPoint.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "ImGui-layer/Example_imguiLayer.h"
#include "ImGui-layer/imgui_interface.h"
#include "RenderContext/CurrentContext.h"
#include "imgui.h"

Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;

Agate::EntryPoint::EntryPoint()
    : deltaTime{0}
{
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::OnEvent), true);
    m_running = true;
    imgui_interface::Init(m_window->GetInstanceWindow());

    //m_layerStack.AddOverlay(new Example_imguiLayer());
    CurrentContext::OpenGL = true;
}

Agate::EntryPoint::~EntryPoint()
{
    imgui_interface::ImguiDestruct();
}

void Agate::EntryPoint::Run()
{
    int frameCount = 0;
    while (m_running)
    {
        frameCount++;
        double FrameTime = m_window->WindowOpenTime();
        Agate::CurrentContext::GetCurrentContex()->NewFrame();

        imgui_interface::BeginFrame();
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++)
        {
            m_layerStack.m_layers.at(i)->OnRender();
        }
        ImGui::Begin("Frame");
        ImGui::Text("%s", ("Per Frame: " + std::to_string(deltaTime * 1000) + " ms").c_str() );
        ImGui::Text("%s", ("Total Frames: " + std::to_string(frameCount )).c_str() );

        ImGui::End();

        imgui_interface::EndFrame();

        m_window->OnUpdate();

        if (std::fmod(frameCount, 25.0) == 0 || frameCount == 1)
        {
            deltaTime = m_window->WindowOpenTime() - FrameTime;
        }
    };
}

void Agate::EntryPoint::OnEvent(Event &e)
{
    EventNotifier notifier(e);

    notifier.NotifyEvent<WindowCloseEvent>(BindFn(EntryPoint::OnWindowClose));
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
Agate::EntryPoint *&Agate::EntryPoint::GetInstance()
{
    return s_instance;
}
float Agate::EntryPoint::GetDeltaTime()
{
    return deltaTime;
}
std::shared_ptr<Agate::Window> Agate::EntryPoint::GetWindow()
{
    return m_window;
}
