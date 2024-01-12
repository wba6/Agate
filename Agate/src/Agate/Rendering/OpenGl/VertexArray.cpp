//
// Created by TANK1_41 on 9/16/2022.
//
#include "agpch.h"
#include "VertexArray.h"
#include "Agate/Core/Logger.h"
#include <glad/glad.h>
namespace Agate
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_vao);
    }


    void VertexArray::Bind()
    {
        glBindVertexArray(m_vao);
    }
    void VertexArray::UnBind()
    {
        glBindVertexArray(0);
    }
    void VertexArray::setUpVertexArray(VertexBuffer &VBO)
    {

        Bind();
        glVertexAttribPointer(0, VBO.getLayout().vertexSize,
                              GL_FLOAT, GL_FALSE, VBO.getLayout().stride, (void *) VBO.getLayout().offset);

        glEnableVertexAttribArray(0);
        UnBind();
    }

}// namespace Agate