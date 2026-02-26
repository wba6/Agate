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
    
    // Create an atomic variable to safely pass the true render time between threads
    std::atomic<double> renderThreadFrameTime{0.0};
    
    // Start Render Thread
    std::jthread renderThread([&]() {
        m_window->AttachContext();        
        double lastRenderTime = m_window->WindowOpenTime();

        while (m_running) {
            Agate::CurrentContext::GetCurrentContex()->NewFrame();

            // Execute game render commands
            Renderer::Flush(); 
            
            // Execute ImGui OpenGL calls
            imgui_interface::Render_GPU();
            
            // Swap buffers (This is what usually blocks on VSync or GPU limits)
            m_window->SwapBuffers(); 

            // Calculate True Render Frame Time
            double currentRenderTime = m_window->WindowOpenTime();
            renderThreadFrameTime.store(currentRenderTime - lastRenderTime, std::memory_order_relaxed);
            lastRenderTime = currentRenderTime;
        }
    });

    int frameCount = 0;
    double lastLogicTime = m_window->WindowOpenTime();

    // Main Thread Game Loop
    while (m_running) {
        frameCount++;
        
        // Calculate Main Thread (Logic) Time
        double currentLogicTime = m_window->WindowOpenTime();
        deltaTime = currentLogicTime - lastLogicTime;
        lastLogicTime = currentLogicTime;

        // Start ImGui CPU Frame
        imgui_interface::BeginFrame();

        // Build your UI - Show BOTH times
        ImGui::Begin("Performance");
        
        // Logic Time (How fast the Main Thread runs)
        ImGui::Text("Logic (Main Thread): %.3f ms", deltaTime * 1000.0);
        
        // True Frame Time (How fast the screen updates)
        double trueRenderTimeMs = renderThreadFrameTime.load(std::memory_order_relaxed) * 1000.0;
        ImGui::Text("Render (True Frame Time): %.3f ms", trueRenderTimeMs);
        ImGui::Text("True FPS: %.1f", 1000.0 / trueRenderTimeMs);
        
        ImGui::Text("Total Frames: %d", frameCount);
        ImGui::End();

        // Update operation (Logic)
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
            m_layerStack.m_layers.at(i)->OnUpdate();
        }

        // Render operation (Submits commands to Queue)
        for (size_t i{0}; i < m_layerStack.m_layers.size(); i++) {
            m_layerStack.m_layers.at(i)->OnRender();
        }

        // Finalize ImGui CPU Frame
        imgui_interface::EndFrame();

        // Poll events
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
