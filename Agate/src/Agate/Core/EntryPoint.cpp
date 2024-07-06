#include "agpch.h"

#include "EntryPoint.h"
#include "Events/Event.h"
#include "ImGui-layer/imgui_interface.h"
#include "RenderContext/CurrentContext.h"
#include "imgui.h"
//TODO: remove these include
#include "glad/glad.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Rendering/OpenGl/VertexArray.h"
#include "Rendering/ModelLoader.h"
#include <filesystem>
#include <iostream>

Agate::EntryPoint *Agate::EntryPoint::s_instance = nullptr;



Agate::EntryPoint::EntryPoint()
    : deltaTime{0}
{
    s_instance = this;

    m_window = std::make_shared<Window>("Agate", 1200, 720, BindFn(EntryPoint::OnEvent), true);
    m_running = true;
    imgui_interface::Init(m_window->GetInstanceWindow());
    //m_layerStack.AddOverlay(new GameObjectsUI);
    //m_layerStack.AddOverlay(new Example_imguiLayer());
    CurrentContext::OpenGL = true;
}

Agate::EntryPoint::~EntryPoint()
{
    imgui_interface::ImguiDestruct();
}

void Agate::EntryPoint::Run()
{
    Shader shader("Shaders/basic.vs.glsl", "Shaders/basic.fg.glsl");
    // load models
    // -----------
    //Model ourModel(std::filesystem::path("Shaders/backpack/backpack.obj").generic_string());
//    float verticesOne[] = {
//            0.5f,  0.5f, 0.0f,  // top right
//            0.5f, -0.5f, 0.0f,  // bottom right
//            -0.5f, -0.5f, 0.0f,  // bottom left
//            -0.5f,  0.5f, 0.0f   // top left
//    };
//
//    std::vector<unsigned int> indexBuffer {  // note that we start from 0!
//            0, 1, 3,  // first Triangle
//            1, 2, 3   // second Triangle
//    };
//
//    IndexBuffer IB(indexBuffer);
//    BufferDataLayout layout{
//            {"triangle", vertexType::Float3},
//    };

//    VertexArray VA(layout, verticesOne, sizeof (verticesOne));
//    VA.addIndexBuffer(IB);

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

        //TODO: abstract this
        //shader.Bind();
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //VA.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //render model
        //ourModel.Draw(shader);

        ImGui::Begin("Frame");
        ImGui::Text("%s", ("Per Frame: " + std::to_string(deltaTime * 1000) + " ms").c_str());
        ImGui::Text("%s", ("Total Frames: " + std::to_string(frameCount)).c_str());

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
    /*e.PrintEventName();*/


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
