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
#include <semaphore>
#include <memory>

Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;


Agate::EntryPoint::EntryPoint()
        : m_deltaTime{0} {
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::OnEvent), true);
    m_running = true;
    imgui_interface::Init(m_window->GetInstanceWindow());

    //m_layerStack.AddOverlay(new GameObjectsUI);
    //m_layerStack.AddOverlay(new Example_imguiLayer());

    CurrentContext::OpenGL = true;
}

Agate::EntryPoint::~EntryPoint() {
    imgui_interface::ImguiDestruct();
}

void Agate::EntryPoint::Run() {

    std::atomic<float> a_RenderThreadFPS{0.0f};
    std::atomic<float> a_RenderThreadMS{0.0f};

    // Limit the Main Thread to be at most 2 frames ahead of the Render Thread
    std::counting_semaphore<2> frameSemaphore(2);

    m_window->DetachContext();
    // Start Render Thread
    std::jthread renderThread([&]() {
        // Get context
        m_window->AttachContext();        
        double lastTime = m_window->WindowOpenTime();
        while (m_running) {
            double frameTime = m_window->WindowOpenTime();
            m_deltaTime = static_cast<float>(frameTime - lastTime);
            lastTime = frameTime;

            // Calculate and store stats for the UI to read
            if (m_deltaTime > 0) {
                a_RenderThreadFPS = 1.0f / m_deltaTime;
                a_RenderThreadMS = m_deltaTime * 1000.0f;
            }
            Agate::CurrentContext::GetCurrentContex()->NewFrame();

            // Execute all commands submitted by the main thread
            Renderer::Flush(); 
            
            // Swap buffers
            m_window->SwapBuffers(); 

            // SIGNAL the Main Thread that we finished a frame
            frameSemaphore.release();
        }
    });

    while (m_running) {

        // wait here if the Render Thread is too far behind
        frameSemaphore.acquire();
        
        // Update operation
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
            m_layerStack.m_layers.at(i)->OnUpdate();
        }

        imgui_interface::BeginFrame();
        // Render operation
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
            m_layerStack.m_layers.at(i)->OnRender();
        }

        ImGui::Begin("Performance");
       
        // Show Main Thread speed (Logic/UI)
        ImGui::Text("Main Thread (UI): %.1f FPS", ImGui::GetIO().Framerate);
        ImGui::Separator();
        // We load from the atomic variables updated by the other thread
        ImGui::Text("Render Thread: %.1f FPS", a_RenderThreadFPS.load());
        ImGui::Text("Render Time: %.3f ms", a_RenderThreadMS.load());
        ImGui::End();

        ImDrawData* data = imgui_interface::EndFrame();

        Renderer::Submit(std::make_unique<DrawUI>(data));


        m_window->PollEvents();
    };
}

void Agate::EntryPoint::OnEvent(Event &e) {
    EventNotifier notifier(e);

    notifier.NotifyEvent<WindowCloseEvent>(BindFn(EntryPoint::OnWindowClose));
    notifier.NotifyEvent<WindowResizedEvent>(BindFn(EntryPoint::OnWindowResized));

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

bool Agate::EntryPoint::OnWindowResized(WindowResizedEvent &e) {
    Renderer::Submit(std::make_unique<SetViewport>(0, 0, e.GetWidth(), e.GetHeight()));
    return false;
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
    return m_deltaTime.load();
}

std::shared_ptr<Agate::Window> Agate::EntryPoint::GetWindow() {
    return m_window;
}
