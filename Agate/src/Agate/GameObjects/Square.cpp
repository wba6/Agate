//
// Created by William Aey on 10/17/2022.
//

#include "Square.h"
#include "Light.h"
#include "Rendering/OpenGl/Render.h"
#include "glad/glad.h"
namespace Agate
{
    int Square::s_instanceNumberCounter = 0;
    void Square::OnEvent(Event &e)
    {
        camera->onEvent(e);
    }

    Square::Square(int xpos, int ypos)
        : GameObject(xpos, ypos, 0.0f),
          m_layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          IBO{indices, STATIC_DRAW},
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


    void Square::setColor(int r, int g, int b, int a)
    {
        color.x = (float) r;
        color.y = (float) g;
        color.z = (float) b;
        color.w = (float) a;
    }
    Square::~Square()
    {
        delete VAO;
    }
    void Square::Render()
    {

        glm::vec3 lightPos = Light::GetLightPosition();
        glm::vec3 cameraPos = camera->getCameraPos();
        m_shader.Bind();
        m_shader.SetUniform3f("objectColor", color.x, color.y, color.z);
        m_shader.SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        m_shader.SetUniform3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
        camera->onUpdate();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_shader.SetUniformMat4("model", model);
        m_shader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

        Render::IndexRender(VAO, VBO, IBO, m_shader);
    }
    GameObjectType Square::GetObjectType()
    {
        return GameObjectType::Square;
    }
    std::string Square::GetObjectString()
    {
        return "Square ";
    }


}// namespace Agate