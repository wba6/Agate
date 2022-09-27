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
    glm::mat4 rotationMat4{1.0f};
    rotationMat4 = glm::rotate(rotationMat4, (float) tri.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    tri.shader.SetUniformMat4("rotation", rotationMat4);

    glDrawArrays(GL_TRIANGLES, 0, indices);
    tri.VBO.UnBind();
    tri.VAO->UnBind();
    tri.shader.UnBind();
}
