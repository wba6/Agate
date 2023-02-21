
#include "Agate.h"
#include <Agate/GameObjects/Cube.h>
#include <Agate/GameObjects/Light.h>
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
        //sqr.rotation = glm::radians(45.0f);
        //tri.rotation = glm::radians(45.0f);
        sqr.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        tri.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        cube.color = {1.0f, 0.0f, 1.0f, 1.0f};
    }

    void Detach() override
    {
    }
    void OnRender() override
    {

        li.Render();
        sqr.Render();
        tri.Render();
        cube.Render();
    };
    void OnEvent(Agate::Event &e) override
    {
        sqr.OnEvent(e);
        tri.OnEvent(e);
        li.OnEvent(e);
        cube.OnEvent(e);
    }
    virtual ~TemplayerEx()
    {
    }
    Agate::Triangle tri{0, 0, 0};
    Agate::Square sqr{1, 0};
    Agate::Light li{2, 0, 3};
    Agate::Cube cube{5, 0, 2};
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    Application->EmplaceLayer(new layerEx);
    Application->EmplaceLayer(new TemplayerEx);

    return Application;
}
