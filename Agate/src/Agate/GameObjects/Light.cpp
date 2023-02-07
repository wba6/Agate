//
// Created by TANK1_41 on 2/6/2023.
//

#include "Light.h"
#include "Rendering/OpenGl/Render.h"

namespace Agate
{
    int Light::s_instanceNumberCounter = 0;

    void Light::Render()
    {
        shader.Bind();

        glm::vec3 camPos = camera->getCameraPos();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, -1.5f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.SetUniformMat4("model", model);

        camera->onUpdate();
        Render::VertexArraryRender(VAO, shader);
    }

    GameObjectType Light::GetObjectType()
    {
        return GameObjectType::Light;
    }
    std::string Light::GetObjectString()
    {
        return "Light";
    }
    Light::Light()
        : Light(0, 0)
    {}
    Light::Light(int x, int y) : GameObject(x, y, 0), layout({0, 3, false, 6 * sizeof(float), 0}),
                                 VBO{vertices, STATIC_DRAW},
                                 IBO{indices, STATIC_DRAW},
                                 shader("Shaders/lighting/1.light_cube.vs.shader", "Shaders/lighting/1.light_cube.fs.shader")
    {
        instanceNumber = ++s_instanceNumberCounter;
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
        camera = new Camera(shader);
        GameObjectsUI::AddObject(this);
    }
    void Light::OnEvent(Event &e)
    {
        camera->onEvent(e);
    }
}// namespace Agate