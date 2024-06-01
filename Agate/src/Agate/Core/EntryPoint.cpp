#include "agpch.h"

#include "EntryPoint.h"
#include "Events/Event.h"
#include "ImGui-layer/imgui_interface.h"
#include "RenderContext/CurrentContext.h"
#include "imgui.h"
//TODO: remove this include
#include "glad/glad.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Rendering/OpenGl/VertexArray.h"

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
    Shader shader("Shaders/Basic.vs.glsl", "Shaders/Basic.fg.glsl");
    float verticesOne[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    std::vector<unsigned int> indexBuffer {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    IndexBuffer IB(indexBuffer);
    BufferDataLayout layout{
            {"triangle", vertexType::Float3},
    };

    VertexArray VA(layout, verticesOne, sizeof (verticesOne));
    VA.addIndexBuffer(IB);

    //TODO: Abstract all of this
/*    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };


    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

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
        shader.Bind();
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        VA.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
