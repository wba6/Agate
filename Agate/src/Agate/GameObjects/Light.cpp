//
// Created by TANK1_41 on 2/6/2023.
//

#include "Light.h"
#include "Rendering/OpenGl/Render.h"

namespace Agate
{
    int Light::s_instanceNumberCounter = 0;
    glm::vec3 Light::s_lightPosition;
    void Light::Render()
    {
        s_lightPosition = {x, y, z};
        m_shader.Bind();

        glm::vec3 camPos = camera->getCameraPos();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::scale(model, {0.5, 0.5, 0.5});
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_shader.SetUniformMat4("model", model);

        camera->onUpdate();
        Render::VertexArraryRender(VAO, m_shader);
    }

    GameObjectType Light::GetObjectType()
    {
        return GameObjectType::Light;
    }
    std::string Light::GetObjectString()
    {
        return "Light";
    }

    Light::Light(int x, int y, int z) : GameObject(x, y, z, 0), m_layout({0, 3, false, 6 * sizeof(float), 0}),
                                        VBO{vertices, STATIC_DRAW},
                                        m_shader("Shaders/lighting/lighting_cube.vs.glsl", "Shaders/lighting/lighting_cube.fg.glsl")
    {
        instanceNumber = ++s_instanceNumberCounter;
        VBO.Bind();
        VAO = new VertexArray(m_layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
        camera = new Camera(m_shader);
        GameObjectsUI::AddObject(this);
        s_lightPosition = {x, y, 0.5};
    }
    void Light::OnEvent(Event &e)
    {
        camera->onEvent(e);
    }
    Light::~Light()
    {
        delete VAO;
        delete camera;
    }

}// namespace Agate