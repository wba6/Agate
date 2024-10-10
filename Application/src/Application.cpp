
#include "Agate.h"
#include <iostream>
#include <string>
#include <filesystem>
class app : public Agate::EntryPoint {

};

class layerEx : public Agate::Layer {

public:
    void Attach() override
    {
        PRINTMSG("Attached example layer");
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
        shader = new Agate::Shader("Shaders/model_loading.vs.glsl", "Shaders/model_loading.fg.glsl");
        camera = new Agate::Camera(*shader);
        camera->setCameraPos({1.0f,1.0f,20.0f});
        camera->setCameraSpeed(10.f);
        model = new Agate::ModelLoader(std::filesystem::path("Shaders\\Cathedral\\TutorialCathedral.fbx").generic_string());
    }

    void Detach() override
    {
    }
    void OnRender() override
    {
        shader->Bind();
        camera->onUpdate();

        glm::mat4 trans_model = glm::mat4(1.0f);
        trans_model = glm::translate(trans_model, glm::vec3(0.0f, 0.0f, 0.0f));// translate it down so it's at the center of the scene
        trans_model = glm::scale(trans_model, glm::vec3(0.5f, 0.5f, 0.5f));    // it's a bit too big for our scene, so scale it down
        shader->SetUniformMat4("model", trans_model);
        model->Draw(*shader);
    }
    void OnEvent(Agate::Event &e) override
    {
        camera->onEvent(e);
    }
    virtual ~TemplayerEx()
    {
    }

    Agate::Shader *shader;
    Agate::Camera *camera;
    Agate::ModelLoader *model;
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    Application->EmplaceLayer(new layerEx);
    Application->EmplaceLayer(new TemplayerEx);

    return Application;
}
