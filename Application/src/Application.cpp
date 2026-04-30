
#include "Agate.h"
#include <array>
#include <atomic>
#include <chrono>
#include <memory>
#include <filesystem>
#include <stdexcept>
#include <string>

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
        PRINTMSG("Detach example layer");
    }

    void OnRender()override
    {
    };

    void OnUpdate()override
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
        modelHandle = Agate::ModelLoader::LoadModel(std::filesystem::path("Shaders/vokselia_spawn/vokselia_spawn.obj").generic_string());
    }

    void Detach() override
    {
    }

    void OnRender() override
    {

        // Poll for model completion until model is retrieved
        if (modelHandle.Status() == Agate::TaskStatus::Done) {
            model = std::make_unique<Agate::ModelEditor>(std::move(modelHandle.Wait().Get()));
            model->LoadTextures();
        } else if (modelHandle.Status() == Agate::TaskStatus::Error) {

            // This will run every frame upon failure
            PRINTCRIT("Failed to load model");
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

    void OnUpdate() override
    {
    };

    void OnEvent(Agate::Event &e) override
    {
        camera->onEvent(e);
    }
    virtual ~TemplayerEx()
    {
        // Tasks not finished
        if ((modelHandle.Status() & Agate::TaskStatus::Terminal) == static_cast<Agate::TaskStatus>(0)) {
            PRINTMSG("[TemplateLayer]: Waiting for pending tasks to finish before destruction...");
            modelHandle.Wait();
        }
    }

    std::unique_ptr<Agate::Shader> shader;
    std::unique_ptr<Agate::Camera> camera;
    std::unique_ptr<Agate::ModelEditor> model;
    Agate::TaskHandle<Agate::ModelEditor> modelHandle;
};
/*
class TaskTestLayer : public Agate::Layer {
private:
    std::atomic<int> taskCounter{ 0 };
    std::array<Agate::TaskHandle<std::size_t>, 5> taskHandles;
    Agate::TaskHandle<std::string> messageHandle;
    std::unique_ptr<std::string> originalMessage = std::make_unique<std::string>("The password is 12345");
    std::unique_ptr<std::string> modifiedMessage = std::make_unique<std::string>("The password is 54321");
    Agate::TaskHandle<std::string> secretMessageHandle;
    Agate::TaskHandle<std::shared_ptr<std::string>> secondSecretMessageHandle;
    Agate::TaskHandle<int> iWillFail;
    Agate::TaskHandle<void> delayedMessageHandle;
public:

    void Attach() override
    {
        messageHandle = Agate::TaskPool::Enqueue([]() -> std::string {
            return "Hello from Task Land";
        });
        for (std::size_t i = 0; i < 5; ++i) {
            taskHandles[i] = Agate::TaskPool::Enqueue([this, i]() -> std::size_t {
                std::this_thread::sleep_for(std::chrono::seconds(5 - i));
                this->taskCounter++;
                return this->taskCounter.load();
            });
        }

        secretMessageHandle = Agate::TaskPool::Enqueue([this]() -> std::string {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return std::string(*this->originalMessage);
        }).Then([this](std::string result) -> void {
            result = *this->modifiedMessage;
        });

        secondSecretMessageHandle = Agate::TaskPool::Enqueue([this]() -> std::shared_ptr<std::string> {
            std::this_thread::sleep_for(std::chrono::seconds(4));
            return std::make_shared<std::string>(*this->originalMessage);
        }).Then([this](std::shared_ptr<std::string> result) -> void {
            *result = *this->modifiedMessage;
        });

        iWillFail = Agate::TaskPool::Enqueue([]() -> int {
            throw std::runtime_error("I failed");
            return 0;
        });
        delayedMessageHandle = Agate::TaskPool::Enqueue([]() -> void {
            std::this_thread::sleep_for(std::chrono::seconds(10));
            PRINTMSG("This message was delayed by 10 seconds");
        }).Then([]() -> void {
            PRINTMSG("This message was printed in a callback after the delayed message");
        });
    }

    void Detach() override
    {
        for (std::size_t i = 0; i < 5; ++i) {
            PRINTMSG("Task {} finished in position {}", i, taskHandles[i].Wait().Get());
        }
        PRINTMSG("{}", messageHandle.Wait().Get());

        PRINTMSG("Secret Message: {}", secretMessageHandle.Wait().Get());
        PRINTMSG("Second Secret Message: {}", *secondSecretMessageHandle.Wait().Get());

        if ((iWillFail.Wait().Status() & Agate::TaskStatus::Error) == Agate::TaskStatus::Error) {
            PRINTMSG("iWillFail failed");
        } else {
            PRINTMSG("iWillFail did not fail");
        }

        delayedMessageHandle.Wait();
    }

    void OnRender()override
    {
    };

    void OnUpdate()override
    {
    };

    void OnEvent(Agate::Event &e) override
    {
    }
};

class TaskPerFrameLayer : public Agate::Layer {
private:
    std::array<Agate::TaskHandle<int>, 1000> bulkHandles;
    std::size_t produced = 0;
    std::size_t consumed = 0;
public:

    void Attach() override
    {

    }

    void Detach() override
    {

    }

    void OnUpdate() override
    {

    }

    void OnRender()override
    {
        if (produced < bulkHandles.size()) {
            bulkHandles[produced++] = Agate::TaskPool::Enqueue([counter = produced]() -> int {
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
                return counter;
            });
            PRINTMSG("Producing {}", produced - 1);
        }

        if (consumed < produced && bulkHandles[consumed].Status() == Agate::TaskStatus::Done) {
            PRINTMSG("Consuming {}", bulkHandles[consumed++].Wait().Get());
        } else if (consumed < produced && bulkHandles[consumed].Status() == Agate::TaskStatus::Error) {
            PRINTWARN("Task {} failed", consumed);
            consumed++;
        }
    };

    void OnEvent(Agate::Event &e) override
    {
    }
};
*/
Agate::EntryPoint* Agate::CreateEntryPoint()
{
    auto Application = new app();

    std::shared_ptr<layerEx> example_layer = std::make_shared<layerEx>();
    //std::shared_ptr<TaskTestLayer> taskTestLayer = std::make_shared<TaskTestLayer>();

    Application->EmplaceLayer(example_layer);
    Application->EmplaceLayer(std::make_shared<TemplayerEx>());
    //Application->EmplaceLayer(taskTestLayer);
    //Application->EmplaceLayer(std::make_shared<TaskPerFrameLayer>());

    Application->RemoveLayer(example_layer);
    //Application->RemoveLayer(taskTestLayer);

    return Application;
}
