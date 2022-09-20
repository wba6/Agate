//
// Created by TANK1_41 on 9/20/2022.
//
#include "agpch.h"

#include "Render.h"
#include <glad/glad.h>

void Agate::Render::RenderTriangles(int indices)
{
    glDrawArrays(GL_TRIANGLES, 0, indices);
}
