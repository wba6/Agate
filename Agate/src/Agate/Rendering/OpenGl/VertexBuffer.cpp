//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Agate
{
    VertexBuffer::VertexBuffer(const float *vertices, int32_t drawtype, size_t data_size)
    {
        glGenBuffers(1, &m_vbo);
        Bind();

        //TODO: how to get the individual size of each buffer without asking for the number of vertices
        glBufferData(GL_ARRAY_BUFFER, data_size, &vertices[0], drawtype);
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
}// namespace Agate