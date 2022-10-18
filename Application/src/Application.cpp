
#include "Agate.h"
#include <Agate/GameObjects/Square.h>
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
    void OnRender()override {
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
        PRINTMSG("Attached triangle layer")
    }

    void Detach() override
    {
    }
    void OnRender() override
    {
        rend.RenderTriagle(tri);
        sqr.rotation = glm::radians(45.0f);
        sqr.Render();
    };
    void OnEvent(Agate::Event &e) override
    {
    }
    virtual ~TemplayerEx()
    {
    }
    Agate::Render rend;
    Agate::Triangle tri{0, 0};
    Agate::Square sqr{};
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    Application->EmplaceLayer(new layerEx);
    Application->EmplaceLayer(new TemplayerEx);

    return Application;
}
