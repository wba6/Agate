#ifndef AGATE_EDITOR_SCENE_HPP
#define AGATE_EDITOR_SCENE_HPP

#include "Agate.h"
#include <memory>
#include <filesystem>

/**
 * @brief Simple Scene class for the Editor to manage rendering objects
 */
class Scene {
public:
    Scene() = default;
    ~Scene() {
        if (m_modelHandle.Status() != Agate::TaskStatus::NullState && (m_modelHandle.Status() & Agate::TaskStatus::Terminal) == static_cast<Agate::TaskStatus>(0)) {
            m_modelHandle.Wait();
        }
    }

    /**
     * @brief Initializes scene resources, shaders, and models
     */
    void Prepare() {
        // Use default shaders from the Agate engine
        m_shader = std::make_unique<Agate::Shader>("Shaders/model_loading.vs.glsl", "Shaders/model_loading.fg.glsl");
        m_camera = std::make_unique<Agate::Camera>(*m_shader);
        
        m_camera->setCameraPos({1.0f, 1.0f, 20.0f});
        m_camera->setCameraSpeed(10.0f);

        // Load a default model asynchronously
        m_modelHandle = Agate::ModelLoader::LoadModel(std::filesystem::path("Shaders/vokselia_spawn/vokselia_spawn.obj").generic_string());
    }

    /**
     * @brief Renders the scene
     */
    void Render() {
        if (!m_shader || !m_camera) return;

        // Check if model loading is complete
        if (!m_model && m_modelHandle.Status() != Agate::TaskStatus::NullState) {
            if (m_modelHandle.Status() == Agate::TaskStatus::Done) {
                m_model = std::make_unique<Agate::ModelEditor>(std::move(m_modelHandle.Wait().Get()));
                m_model->LoadTextures();
            }
        }

        m_shader->Bind();
        m_camera->onUpdate();

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        // Center the model
        m_shader->SetUniform3f("pointLight.Position", m_camera->getCameraPos().x, m_camera->getCameraPos().y, m_camera->getCameraPos().z);
        
        // Default transform
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        m_shader->SetUniformMat4("model", modelMatrix);

        if (m_model) {
            m_model->Draw(*m_shader);
        }
    }

    /**
     * @brief Event handler for the scene
     * 
     * @param e Event to handle
     */
    void OnEvent(Agate::Event &e) {
        if (m_camera) {
            m_camera->onEvent(e);
        }
    }

private:
    std::unique_ptr<Agate::Shader> m_shader;
    std::unique_ptr<Agate::Camera> m_camera;
    std::unique_ptr<Agate::ModelEditor> m_model;
    Agate::TaskHandle<Agate::ModelEditor> m_modelHandle;
};

#endif // AGATE_EDITOR_SCENE_HPP
