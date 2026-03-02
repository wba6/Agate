#include "agpch.h"

#include "EntryPoint.h"
#include "Events/Event.h"
#include "ImGui-layer/imgui_interface.h"
#include "RenderContext/CurrentContext.h"
#include "Rendering/Renderer.hpp"
#include "Events/RenderCommand.hpp"
#include "ImGui-layer/Example_imguiLayer.h"
#include "imgui.h"
#include <thread>
#include <memory>

Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;


Agate::EntryPoint::EntryPoint()
        : deltaTime{0} {
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::OnEvent), true);
    m_running = true;
    imgui_interface::Init(m_window->GetInstanceWindow());

    //m_layerStack.AddOverlay(new GameObjectsUI);
    //m_layerStack.AddOverlay(new Example_imguiLayer());

    CurrentContext::OpenGL = true;

    std::unique_ptr<DrawMesh> mesh = std::make_unique<DrawMesh>(1);
    Renderer::Submit(std::move(mesh));
}

Agate::EntryPoint::~EntryPoint() {
    imgui_interface::ImguiDestruct();
}

void Agate::EntryPoint::Run() {

    m_window->DetachContext();
    // Start Render Thread
    std::jthread renderThread([&]() {
        // Get context
        m_window->AttachContext();        
        int frameCount = 0;
        while (m_running) {
            frameCount++;
            double FrameTime = m_window->WindowOpenTime();
            Agate::CurrentContext::GetCurrentContex()->NewFrame();

            // Execute all commands submitted by the main thread
            Renderer::Flush(); 
            
            // Swap buffers
            m_window->SwapBuffers(); 

            if (std::fmod(frameCount, 25.0) == 0 || frameCount == 1) {
                deltaTime = m_window->WindowOpenTime() - FrameTime;
            }

        }
    });

    while (m_running) {
        
        // Update operation
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
            m_layerStack.m_layers.at(i)->OnUpdate();
        }

        imgui_interface::BeginFrame();
        // Render operation
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
            m_layerStack.m_layers.at(i)->OnRender();
        }

        ImGui::Begin("Frame");
        //ImGui::Text("%s", ("Per Frame: " + std::to_string(deltaTime * 1000) + " ms").c_str());
        //ImGui::Text("%s", ("Total Frames: " + std::to_string(frameCount)).c_str());
        ImGui::End();
        ImDrawData* data = imgui_interface::EndFrame();

        Renderer::Submit(std::make_unique<DrawUI>(data));


        m_window->PoolEvents();
    };
}

void Agate::EntryPoint::OnEvent(Event &e) {
    EventNotifier notifier(e);

    notifier.NotifyEvent<WindowCloseEvent>(BindFn(EntryPoint::OnWindowClose));

    for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
        m_layerStack.m_layers.at(i)->OnEvent(e);
        if (e.Handled())
            break;
    }
}


bool Agate::EntryPoint::OnWindowClose(WindowCloseEvent &e) {
    m_running = false;
    return true;
}

void Agate::EntryPoint::EmplaceLayer(std::shared_ptr<Layer> layer) {
    m_layerStack.AddLayer(std::move(layer));
}

void Agate::EntryPoint::RemoveLayer(std::shared_ptr<Layer> layer) {
    m_layerStack.RemoveLayer(std::move(layer));
}

void Agate::EntryPoint::EmplaceOverlay(std::shared_ptr<Layer> overlay) {
    m_layerStack.AddOverlay(std::move(overlay));
}

void Agate::EntryPoint::RemoveOverlay(std::shared_ptr<Layer> overlay) {
    m_layerStack.RemoveOverlay(std::move(overlay));
}

Agate::EntryPoint *&Agate::EntryPoint::GetInstance() {
    return s_instance;
}

float Agate::EntryPoint::GetDeltaTime() {
    return deltaTime;
}

std::shared_ptr<Agate::Window> Agate::EntryPoint::GetWindow() {
    return m_window;
}
