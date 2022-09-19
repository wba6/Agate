//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexBuffer.h"
#include <glad/glad.h>
int8_t DrawTypes::STREAM_DRAW = 0x88E0;
int8_t DrawTypes::STREAM_READ = 0x88E1;
int8_t DrawTypes::STREAM_COPY = 0x88E2;
int8_t DrawTypes::STATIC_DRAW = 0x88E4;
int8_t DrawTypes::STATIC_READ = 0x88E5;
int8_t DrawTypes::STATIC_COPY = 0x88E6;
int8_t DrawTypes::DYNAMIC_DRAW = 0x88E8;
int8_t DrawTypes::DYNAMIC_READ = 0x88E9;
int8_t DrawTypes::DYNAMIC_COPY = 0x88EA;

VertexBuffer::VertexBuffer(float *data, size_t dataSize, int8_t drawtype)
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
