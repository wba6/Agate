//
// Created by William Aey on 10/17/2022.
//

#include "IndexBuffer.h"
#include <glad/glad.h>
#include "OpenGLCheck.h"

namespace Agate {
    IndexBuffer::IndexBuffer(const std::vector<unsigned int> &vector)
            : m_indinces(vector) {
        GLCall(glGenBuffers(1, &m_ibo));
    }

    void IndexBuffer::Bind() {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
    }

    void IndexBuffer::UnBind() {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    unsigned int IndexBuffer::GetNumOfIndices() const {
        return m_indinces.size();
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_ibo);
    }

    void IndexBuffer::setUpBuffer() {
        Bind();

        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indinces.size() * sizeof(unsigned int), &m_indinces[0], STATIC_DRAW));
    }
}// namespace Agate