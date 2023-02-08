//
// Created by TANK1_41 on 9/20/2022.
//
#include "agpch.h"

#include "Render.h"
#include "VertexBuffer.h"
#include <glad/glad.h>

long int Agate::Render::framesRendered;

void Agate::Render::IndexRender(Agate::VertexArray *&vao, Agate::VertexBuffer &vbo, Agate::IndexBuffer &ibo, Shader &shader)
{
    vao->Bind();
    ibo.Bind();


    glDrawElements(GL_TRIANGLES, ibo.GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);

    shader.UnBind();
    ibo.UnBind();
    vao->UnBind();
}
long int Agate::Render::GetRenderedFrames()
{
    return framesRendered;
}
void Agate::Render::VertexArraryRender(Agate::VertexArray *&vao, Agate::Shader &shader)
{
    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    shader.UnBind();
    vao->UnBind();
}
