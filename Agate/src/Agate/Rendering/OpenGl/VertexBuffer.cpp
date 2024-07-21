//
// Created by TANK1_41 on 9/16/2022.
//

#include "VertexBuffer.h"
#include "OpenGLCheck.h"

#include <glad/glad.h>

namespace Agate {
    VertexBuffer::VertexBuffer(const void *vertices, int32_t drawtype, size_t data_size) {
        GLCall(glGenBuffers(1, &m_vbo));
        Bind();

        GLCall(glBufferData(GL_ARRAY_BUFFER, data_size, vertices, drawtype));
        UnBind();

    }

    void VertexBuffer::Bind() {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    }

    void VertexBuffer::UnBind() {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}// namespace Agate