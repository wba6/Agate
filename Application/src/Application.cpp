
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
        sqr.rotation = glm::radians(45.0f);
        tri.rotation = glm::radians(45.0f);
        sqr.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        tri.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    }

    void Detach() override
    {
    }
    void OnRender() override
    {


        sqr.Render();
        sqr2.Render();
        tri.Render();
    };
    void OnEvent(Agate::Event &e) override
    {
        sqr.OnEvent(e);
        sqr2.OnEvent(e);
        tri.OnEvent(e);
    }
    virtual ~TemplayerEx()
    {
    }
    Agate::Triangle tri{0, 0};
    Agate::Square sqr{1, 0};
    Agate::Square sqr2{2, 0};
    int rotation;
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    Application->EmplaceLayer(new layerEx);
    Application->EmplaceLayer(new TemplayerEx);

    return Application;
}
