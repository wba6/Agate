//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Agate {
    VertexBuffer::VertexBuffer(const void *vertices, int32_t drawtype, size_t data_size) {
        glGenBuffers(1, &m_vbo);
        Bind();

        glBufferData(GL_ARRAY_BUFFER, data_size, vertices, drawtype);
        UnBind();

    }

    void VertexBuffer::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    }

    void VertexBuffer::UnBind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}// namespace Agate