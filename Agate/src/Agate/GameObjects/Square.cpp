//
// Created by William Aey on 10/17/2022.
//

#include "Square.h"
#include "Rendering/OpenGl/Render.h"

namespace Agate
{
    int Square::s_instanceNumberCounter = 0;
    void Square::OnEvent(Event &e)
    {
        camera->onEvent(e);
    }

    Square::Square(int xpos, int ypos)
        : GameObject(xpos, ypos, 0.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          IBO{indices, STATIC_DRAW},
          shader("Shaders/Basic.vs.glsl", "Shaders/Basic.fg.glsl")
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
        shader.Bind();

        shader.SetUniform4f("Ucolors", color.x, color.y, color.z, color.w);
        camera->onUpdate();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(x, y, 0));
        model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetUniformMat4("model", model);

        Render::IndexRender(VAO, VBO, IBO, shader);
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