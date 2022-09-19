//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexArray.h"

#include <glad/glad.h>
VertexArray::VertexArray(VertexLayOut vertexLayOut)
{
    glGenVertexArrays(1, &m_vao);
    Bind();
    glVertexAttribPointer(vertexLayOut.layoutNum, vertexLayOut.vertexSize,
                          GL_FLOAT, GL_FALSE, vertexLayOut.stride, (void *) vertexLayOut.offset);

    glEnableVertexAttribArray(vertexLayOut.layoutNum);
    UnBind();
}
void VertexArray::Bind()
{
    glBindVertexArray(m_vao);
}
void VertexArray::UnBind()
{
    glBindVertexArray(0);
}
