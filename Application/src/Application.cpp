
#include "Agate.h"
#include <iostream>
#include <string>
class app : public Agate::EntryPoint {

};

class layerEx : public Agate::Layer {

public:
    void Attach() override
    {
        PRINTMSG("Attached example layer")
    }

    void Detach() override
    {
    }
    void onRender()override {
            ImGui::Begin("window 2");
            ImGui::Text("Hello world");
            ImGui::End();
    };
    void OnEvent(Agate::Event &e) override
    {
    }
};

class TemplayerEx : public Agate::Layer {

public:
    TemplayerEx() = default;

    void Attach() override
    {
        PRINTMSG("Attached example layer")
        VBO = new Agate::VertexBuffer(vertices, sizeof(vertices), STATIC_DRAW);
        VBO->Bind();

        Agate::VertexLayOut vaData{0, 3, false, 3 * sizeof(float), 0};
        VAO = new Agate::VertexArray(vaData);
        VAO->Bind();
        shader.bind();
    }

    void Detach() override
    {
    }
    void onRender() override
    {
        //rotationMat4 = glm::rotate(rotationMat4, (float) 1.0, glm::vec3(1.0f, 1.0f, 1.0f));
        shader.SetUniform4f("Ucolors", 1.0, 0.2f, 0.2f, 1.0f);
        shader.SetUniformMat4("rotation", rotationMat4);
        Agate::Render rend;
        rend.RenderTriangles(3);
    };
    void OnEvent(Agate::Event &e) override
    {
    }
    virtual ~TemplayerEx()
    {
        delete VAO;
        delete VBO;
    }
    Agate::VertexArray *VAO;
    Agate::VertexBuffer *VBO;
    glm::mat4 rotationMat4{1.0f};
    Agate::Shader shader = Agate::Shader("Shaders/Basic.vs.shader", "Shaders/Basic.fg.shader");
    float vertices[9] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};
};
Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    Application->EmplaceLayer(new layerEx);
    Application->EmplaceLayer(new TemplayerEx);

    return Application;
}
