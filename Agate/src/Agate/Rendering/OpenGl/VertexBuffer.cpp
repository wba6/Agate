//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Agate
{
    VertexBuffer::VertexBuffer(const float *vertices, unsigned vertCount, int32_t drawtype)
    {
        glGenBuffers(1, &m_vbo);
        Bind();


        glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(float), &vertices[0], drawtype);
        UnBind();

        m_vertexLayOut.Normilized = false;
        //TODO: layout num
        m_vertexLayOut.layoutNum = 0;
        m_vertexLayOut.vertexSize = vertCount;
        m_vertexLayOut.stride = vertCount * sizeof (float);
        m_vertexLayOut.offset = 0;
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