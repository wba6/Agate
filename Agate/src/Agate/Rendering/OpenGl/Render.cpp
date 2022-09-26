//
// Created by TANK1_41 on 9/20/2022.
//
#include "agpch.h"

#include "Render.h"
#include <glad/glad.h>
#include "VertexBuffer.h"

void Agate::Render::RenderTriagle(Triangle &tri)
{
    Shader shader = Shader("Shaders/Basic.vs.shader", "Shaders/Basic.fg.shader");
    int indices = static_cast<int>(tri.vertices.size()) / tri.layout.vertexSize;

    VertexBuffer VBO{tri.vertices, STATIC_DRAW};
    VBO.Bind();

    VertexArray VAO(tri.layout);
    VAO.Bind();

    shader.Bind();
    shader.SetUniform4f("Ucolors", tri.color.x, tri.color.y, tri.color.z, tri.color.w);
    glm::mat4 rotationMat4{1.0f};
    rotationMat4 = glm::rotate(rotationMat4, (float) tri.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    shader.SetUniformMat4("rotation", rotationMat4);

    glDrawArrays(GL_TRIANGLES, 0, indices);
    VBO.UnBind();
    VAO.UnBind();
    shader.UnBind();
}
