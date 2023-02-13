//
// Created by TANK1_41 on 2/13/2023.
//

#include "Cube.h"
#include "Light.h"
#include "Rendering/OpenGl/Render.h"
namespace Agate
{
    int Cube::s_instanceNumberCounter = 0;
    void Cube::Render()
    {
        glm::vec3 lightPos = Light::GetLightPosition();
        glm::vec3 cameraPos = camera->getCameraPos();
        m_shader.Bind();
        m_shader.SetUniform3f("objectColor", color.x, color.y, color.z);
        m_shader.SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        m_shader.SetUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
        camera->onUpdate();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, z));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_shader.SetUniformMat4("model", model);
        m_shader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

        Render::VertexArraryRender(VAO, m_shader);
    }

    GameObjectType Cube::GetObjectType()
    {
        return GameObjectType::Cube;
    }
    std::string Cube::GetObjectString()
    {
        return "Cube";
    }
    Cube::Cube(int x, int y, int z) : GameObject(x, y, z, 0), m_layout({0, 3, false, 6 * sizeof(float), 0}),
                                      VBO{vertices, STATIC_DRAW},
                                      m_shader("Shaders/lighting/colors_lighting.vs.glsl", "Shaders/lighting/colors_lighting.fg.glsl")
    {
        instanceNumber = ++s_instanceNumberCounter;
        VBO.Bind();
        VAO = new VertexArray(m_layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
        camera = new Camera(m_shader);
        GameObjectsUI::AddObject(this);
    }
    void Cube::OnEvent(Event &e)
    {
        camera->onEvent(e);
    }
    void Cube::setColor(int r, int g, int b, int a)
    {
        color = {r, g, b, a};
    }
    Cube::~Cube()
    {
        delete VAO;
        delete camera;
    }

}// namespace Agate