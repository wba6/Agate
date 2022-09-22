
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
    }

    void Detach() override
    {
    }
    void onRender() override
    {
        rend.RenderTriagle(vertices,{0, 3, false, 3 * sizeof(float), 0},{1.0, 0.2f, 0.2f, 1.0f}, 0.0);
    };
    void OnEvent(Agate::Event &e) override
    {
    }
    virtual ~TemplayerEx()
    {

    }
    Agate::Render rend;
    std::vector<float> vertices = {
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
