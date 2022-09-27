//
// Created by TANK1_41 on 9/26/2022.
//

#include "Triangle.h"

namespace Agate
{

    void Triangle::OnEvent(Event &e)
    {
    }
    void Triangle::OnRender()
    {

    }
    Triangle::Triangle(int xpos, int ypos)
        : x(xpos), y(ypos), rotation(0.0f), color(1.0f, 1.0f, 1.0f, 1.0f),
          layout({0, 3, false, 3 * sizeof(float), 0}),
          VBO{vertices, STATIC_DRAW},
          shader("Shaders/Basic.vs.shader", "Shaders/Basic.fg.shader")
    {
        VBO.Bind();
        VAO = std::make_unique<VertexArray>(layout);
        VAO->Bind();
        VBO.UnBind();
        VAO->UnBind();
    }
}// namespace Agate