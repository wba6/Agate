//
// Created by William Aey on 10/17/2022.
//

#include "IndexBuffer.h"
#include <glad/glad.h>

namespace Agate {
    IndexBuffer::IndexBuffer(std::vector<unsigned int> &vector)
            : m_indinces(vector) {
        glGenBuffers(1, &m_ibo);
    }

    void IndexBuffer::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }

    void IndexBuffer::UnBind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    unsigned int IndexBuffer::GetNumOfIndices() const {
        return m_indinces.size();
    }

    IndexBuffer::~IndexBuffer() {
    }

    void IndexBuffer::setUpBuffer() {
        Bind();

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indinces.size() * sizeof(float), &m_indinces[0], STATIC_DRAW);
    }
}// namespace Agate