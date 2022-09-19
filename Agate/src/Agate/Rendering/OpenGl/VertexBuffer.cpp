//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexBuffer.h"
#include <glad/glad.h>


VertexBuffer::VertexBuffer(float *data, size_t dataSize, int32_t drawtype)
{
    glGenBuffers(1, &m_vbo);
    Bind();


    glBufferData(GL_ARRAY_BUFFER, dataSize, data, drawtype);
    UnBind();
}
void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}
void VertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
