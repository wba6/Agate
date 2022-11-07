//
// Created by TANK1_41 on 9/26/2022.
//

#include "Triangle.h"
#include "Rendering/OpenGl/Render.h"

namespace Agate
{

    void Triangle::OnEvent(Event &e)
    {
    }

    Triangle::Triangle(int xpos, int ypos)
        :  GameObject(0,0,0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          IBO{indices,STATIC_DRAW},
          VBO{vertices, STATIC_DRAW},
          shader("Shaders/Basic.vs.glsl", "Shaders/Basic.fg.glsl")
    {
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
    }
    Triangle::Triangle()
        :  GameObject(0,0,0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          IBO{indices,STATIC_DRAW},
          VBO{vertices, STATIC_DRAW},
          shader("Shaders/Basic.vs.glsl", "Shaders/Basic.fg.glsl")
    {
        VBO.Bind();
        VAO = new VertexArray(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
    }
    void Triangle::setXPos(int xPos)
    {
        x = xPos;
    }
    void Triangle::setYPos(int yPos)
    {
        y = yPos;
    }
    void Triangle::setColor(int r, int g, int b, int a)
    {
        color.x = (float) r;
        color.y = (float) g;
        color.z = (float) b;
        color.w = (float) a;
    }
    void Triangle::Render()
    {
        shader.Bind();


        shader.SetUniform4f("Ucolors", color.x, color.y, color.z, color.w);
        glm::mat4 transformations{1.0f};
        transformations = glm::translate(transformations, glm::vec3(x, y, 0));
        transformations = glm::rotate(transformations, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetUniformMat4("transformations", transformations);

        Render::IndexRender(VAO,VBO,IBO,shader);


    }
    Triangle::~Triangle()
    {
        delete VAO;
    }


}// namespace Agate