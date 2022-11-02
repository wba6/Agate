//
// Created by William Aey on 10/17/2022.
//

#include "Square.h"
#include "Rendering/OpenGl/Render.h"
namespace Agate
{
    void Square::OnEvent(Event &e)
    {
        camera->onEvent(e);
    }

    Square::Square(int xpos, int ypos)
        :  GameObject(0,0,0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          IBO{indices,STATIC_DRAW},
          shader("Shaders/Basic.vs.glsl", "Shaders/Basic.fg.glsl")
    {
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
    }
    Square::Square()
        : GameObject(0,0,0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          IBO{indices,STATIC_DRAW},
          shader("Shaders/Basic.vs.glsl", "Shaders/Basic.fg.glsl")
    {
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
        camera = new Camera(shader);
    }
    void Square::setXPos(int xPos)
    {
        x = xPos;
    }
    void Square::setYPos(int yPos)
    {
        y = yPos;
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
        delete camera;
        delete VAO;
    }
    void Square::Render()
    {
        shader.Bind();

        shader.SetUniform4f("Ucolors", color.x, color.y, color.z, color.w);
        camera->onUpdate();

        glm::mat4 model = glm::mat4(1.0f);
        shader.SetUniformMat4("model", model);

        Render::IndexRender(VAO, VBO, IBO, shader);
    }
}// namespace Agate