//
// Created by TANK1_41 on 9/16/2022.
//

#ifndef AGATE_VERTEXARRAY_H
#define AGATE_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "IndexBuffer.h"

namespace Agate {
    class VertexArray {
    public:
        //takes in a data layout and the data through a void pointer
        VertexArray(BufferDataLayout bufferInformation, float *data, size_t data_size);

        /**
         * Adds index buffer to the vertex array
         * @param indexBuffer
         */
        void addIndexBuffer(IndexBuffer indexBuffer);

        void Bind();

        void UnBind();

    private:
        unsigned int m_vao;
    };

}// namespace Agate
#endif//AGATE_VERTEXARRAY_H
