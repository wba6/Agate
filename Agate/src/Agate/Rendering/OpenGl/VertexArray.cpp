//
// Created by TANK1_41 on 9/16/2022.
//
#include "agpch.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Agate/Core/Logger.h"
#include <glad/glad.h>
namespace Agate
{

    void VertexArray::Bind()
    {
        glBindVertexArray(m_vao);
    }
    void VertexArray::UnBind()
    {
        glBindVertexArray(0);
    }
    VertexArray::VertexArray(BufferDataLayout bufferInformation, float* data, size_t data_size)
    {
        glGenVertexArrays(1, &m_vao);
        VertexBuffer VBO(data, STATIC_DRAW, data_size);
        VBO.Bind();
        for (int i = 0; i < bufferInformation.getAttributes().size(); ++i)
        {
            Bind();
            glVertexAttribPointer(i, bufferInformation.getVerticieCount(bufferInformation.getAttributes().at(i).type),
                                  GL_FLOAT, bufferInformation.getAttributes().at(i).normalized, bufferInformation.getStride()
                                  ,(void *) bufferInformation.getAttributes().at(i).offset);

            glEnableVertexAttribArray(i);
            UnBind();
        }
    }

}// namespace Agate