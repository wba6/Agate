
#include "Agate.h"
#include <chrono>
#include <memory>
#include <filesystem>
#include <future>
class app : public Agate::EntryPoint {

};

class layerEx : public Agate::Layer {

public:
    void Attach() override
    {
        PRINTMSG("Attached example layer");
        PRINTMSG("Detected Process Concurrency: {}", Agate::ProcessConcurrency());
    }

    void Detach() override
    {

        // Test making a task
        {
            auto taskFn = []() -> int {
                PRINTMSG("Hello from Task Land");
                return 0;
            };
            using FnType = decltype(taskFn);
            using CleanType = std::decay_t<FnType>;
            std::unique_ptr<Agate::Task> task = std::make_unique<Agate::QualifiedTask<CleanType>>(std::forward<FnType>(taskFn));
            task->Run();
        }

        // Test making a task's callback and state
        {
            auto integerCallback = [](int result) -> void {
                PRINTMSG("Callback land reports a result of {}", result);
            };
            using FnType = decltype(integerCallback);
            using CleanType = std::decay_t<FnType>;
            std::unique_ptr<Agate::TaskCallback<int>> callback 
                    = std::make_unique<Agate::QualifiedCallback<int, CleanType>>(
                std::forward<FnType>(integerCallback)
            );
            std::unique_ptr<Agate::QualifiedTaskState<int>> state
                    = std::make_unique<Agate::QualifiedTaskState<int>>();
            state->callback = std::move(callback);
            state->result.emplace(1);
            state->callback->Run(*(state->result));
        }

        PRINTMSG("Detach example layer");
    }

    void OnRender()override
    {
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
        shader = std::make_unique<Agate::Shader>("Shaders/model_loading.vs.glsl", "Shaders/model_loading.fg.glsl");
        camera = std::make_unique<Agate::Camera>(*shader);
        camera->setCameraPos({1.0f,1.0f,20.0f});
        camera->setCameraSpeed(10.f);
        model = nullptr;
        pendingModel = Agate::ModelLoader::LoadModel(std::filesystem::path("Shaders/vokselia_spawn/vokselia_spawn.obj").generic_string());
    }

    void Detach() override
    {
    }

    void OnRender() override
    {

        // Poll for model completion until model is retrieved
        if (pendingModel.valid()) {
            const auto status = pendingModel.wait_for(std::chrono::seconds(0));
            if (status == std::future_status::ready) {
                model = pendingModel.get();
                model->LoadTextures();
            }
        }

        shader->Bind();
        camera->onUpdate();

        glm::mat4 trans_model = glm::mat4(1.0f);
        trans_model = glm::translate(trans_model, glm::vec3(0.0f, 0.0f, 0.0f));// translate it down so it's at the center of the scene
        shader->SetUniform3f("pointLight.Position", camera->getCameraPos().x,camera->getCameraPos().y,camera->getCameraPos().z);    // Position: (x, y, z)
        trans_model = glm::scale(trans_model, glm::vec3(1.0f, 1.5f, 0.55f));    // it's a bit too big for our scene, so scale it down
        shader->SetUniformMat4("model", trans_model);

        // Only attempt to draw if model has been retrieved
        if (model) {
            model->Draw(*shader);
        }
    }
    void OnEvent(Agate::Event &e) override
    {
        camera->onEvent(e);
    }
    virtual ~TemplayerEx()
    {
        if (pendingModel.valid()) {
            PRINTMSG("[TemplateLayer]: Waiting for pending model");
            pendingModel.wait();
            model = pendingModel.get();
        }
    }

    std::unique_ptr<Agate::Shader> shader;
    std::unique_ptr<Agate::Camera> camera;
    std::unique_ptr<Agate::ModelEditor> model;
    std::future<std::unique_ptr<Agate::ModelEditor>> pendingModel;
};

Agate::EntryPoint *Agate::CreateEntryPoint()
{
    auto Application = new app();

    std::shared_ptr<layerEx> example_layer = std::make_shared<layerEx>();

    Application->EmplaceLayer(example_layer);
    Application->EmplaceLayer(std::make_shared<TemplayerEx>());

    Application->RemoveLayer(example_layer);

    return Application;
}
