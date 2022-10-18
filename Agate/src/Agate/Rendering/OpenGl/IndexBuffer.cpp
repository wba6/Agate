//
// Created by William Aey on 10/17/2022.
//

#include "IndexBuffer.h"
#include <glad/glad.h>
namespace Agate
{
    IndexBuffer::IndexBuffer(std::vector<unsigned int> &vector, int32_t drawtype)
    :m_indinces(vector)
    {
        glGenBuffers(1, &m_ibo);
        Bind();


        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indinces.size() * sizeof (float), &m_indinces[0], drawtype);
        UnBind();
    }
    void IndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    }
    void IndexBuffer::UnBind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    unsigned int IndexBuffer::GetNumOfIndices() const
    {
        return m_indinces.size();
    }
    IndexBuffer::~IndexBuffer()
    {
    }
}// namespace Agate