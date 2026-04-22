#include "Scene.hpp"
#include "Agate.h"

#include <memory>
#include <filesystem>

Scene::~Scene() {
    if (m_modelHandle.Status() != Agate::TaskStatus::NullState && (m_modelHandle.Status() & Agate::TaskStatus::Terminal) == static_cast<Agate::TaskStatus>(0)) {
        m_modelHandle.Wait();
    }
}

void Scene::Prepare() {
    // Use default shaders from the Agate engine
    m_shader = std::make_unique<Agate::ShaderUser>("Shaders/model_loading.vs.glsl", "Shaders/model_loading.fg.glsl");
    m_camera = std::make_unique<Agate::Camera>(*m_shader);
    
    m_camera->setCameraPos({1.0f, 1.0f, 20.0f});
    m_camera->setCameraSpeed(10.0f);

    // Load a default model asynchronously
    m_modelHandle = Agate::ModelLoader::LoadModel(std::filesystem::path("Shaders/backpack/backpack.obj").generic_string(), true);

    // Default transform
    m_transform = glm::mat4(1.0f);
    m_transform = glm::translate(m_transform, glm::vec3(0.0f, 0.0f, 0.0f));
    m_transform = glm::scale(m_transform, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Scene::Render() {
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

    // Center the model
    m_shader->SetUniform3f("pointLight.Position", m_camera->getCameraPos().x, m_camera->getCameraPos().y, m_camera->getCameraPos().z);
    m_shader->SetUniformMat4("model", m_transform);

    if (m_model) {
        m_model->Draw(*m_shader);
    }
}

void Scene::OnEvent(Agate::Event &e) {
    if (m_camera) {
        m_camera->onEvent(e);
    }
}

void Scene::SetViewportSize(float width, float height) {
    if (m_camera) {
        m_camera->SetViewportSize(width, height);
    }
}

void Scene::SetModelTransform(glm::mat4 transform) {
    m_transform = transform;
}
