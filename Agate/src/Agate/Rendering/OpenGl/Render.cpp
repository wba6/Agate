//
// Created by TANK1_41 on 9/20/2022.
//
#include "agpch.h"

#include "Render.h"
#include <glad/glad.h>
#include "VertexBuffer.h"

void Agate::Render::RenderTriagle(Triangle &tri)
{
    tri.OnRender();
    int indices = static_cast<int>(tri.vertices.size()) / tri.layout.vertexSize;
    tri.VBO.Bind();
    tri.VAO->Bind();


    tri.shader.Bind();
    tri.shader.SetUniform4f("Ucolors", tri.color.x, tri.color.y, tri.color.z, tri.color.w);
    static glm::mat4 transformations{1.0f};
    transformations = glm::translate(transformations, glm::vec3(tri.x, tri.y, 0));
    transformations = glm::rotate(transformations, (float) tri.rotation, glm::vec3(0.0f, 0.0f, 1.0f));

    tri.shader.SetUniformMat4("transformations", transformations);

    glDrawArrays(GL_TRIANGLES, 0, indices);
    tri.VBO.UnBind();
    tri.VAO->UnBind();
    tri.shader.UnBind();
}
void Agate::Render::IndexRender(Agate::VertexArray*& vao, Agate::VertexBuffer& vbo, Agate::IndexBuffer& ibo, Shader& shader)
{
    vao->Bind();
    ibo.Bind();


    glDrawElements(GL_TRIANGLES, ibo.GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);

    shader.UnBind();
    ibo.UnBind();
    vao->UnBind();
}
