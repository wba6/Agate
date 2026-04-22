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
    ~Scene();

    /**
     * @brief Initializes scene resources, shaders, and models
     */
    void Prepare();

    /**
     * @brief Renders the scene
     */
    void Render();

    /**
     * @brief Event handler for the scene
     * 
     * @param e Event to handle
     */
    void OnEvent(Agate::Event &e);

    /**
     * @brief Updates the viewport size for the scene's camera
     * 
     * @param width New width of the viewport
     * @param height New height of the viewport
     */
    void SetViewportSize(float width, float height);

private:
    std::unique_ptr<Agate::ShaderUser> m_shader;
    std::unique_ptr<Agate::Camera> m_camera;
    std::unique_ptr<Agate::ModelEditor> m_model;
    Agate::TaskHandle<Agate::ModelEditor> m_modelHandle;
};

#endif // AGATE_EDITOR_SCENE_HPP
