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
        /*shader.Bind();


        shader.SetUniform4f("Ucolors", color.x, color.y, color.z, color.w);
        camera->onUpdate();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0));
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetUniformMat4("model", model);
        shader.SetUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
        shader.SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);

        Render::IndexRender(VAO, VBO, IBO, shader);*/
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
    Light::Light(int x, int y) : GameObject(x, y, 0), layout({0, 3, false, 3 * sizeof(float), 0}),
                                 VBO{vertices, STATIC_DRAW},
                                 IBO{indices, STATIC_DRAW},
                                 shader("Shaders/lighting/light_cube.vs.shader", "Shaders/lighting/light_cube.fg.shader")
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
}// namespace Agate