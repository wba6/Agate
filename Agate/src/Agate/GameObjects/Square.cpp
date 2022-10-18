//
// Created by William Aey on 10/17/2022.
//

#include "Square.h"
#include "Rendering/OpenGl/Render.h"
namespace Agate
{
    void Square::OnEvent(Event &e)
    {
    }
    void Square::OnRenderLocal()
    {
        shader.Bind();


        shader.SetUniform4f("Ucolors", color.x, color.y, color.z, color.w);
        glm::mat4 transformations{1.0f};
        transformations = glm::translate(transformations, glm::vec3(x, y, 0));
        transformations = glm::rotate(transformations, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetUniformMat4("transformations", transformations);



    }
    Square::Square(int xpos, int ypos)
        : x(xpos), y(ypos), rotation(0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          IBO{indices,STATIC_DRAW},
          shader("Shaders/Basic.vs.shader", "Shaders/Basic.fg.shader")
    {
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
    }
    Square::Square()
        : x(0), y(0), rotation(0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          IBO{indices,STATIC_DRAW},
          shader("Shaders/Basic.vs.shader", "Shaders/Basic.fg.shader")
    {
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
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
        delete VAO;
    }
    void Square::Render()
    {
        OnRenderLocal();
        Render::IndexRender(VAO,VBO,IBO,shader);

    }
}// namespace Agate