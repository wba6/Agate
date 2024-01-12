//
// Created by TANK1_41 on 9/16/2022.
//

#ifndef AGATE_VERTEXARRAY_H
#define AGATE_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexLayout.h"
namespace Agate
{
    class VertexArray {
    public:
        explicit VertexArray(VertexBuffer VBO);
        void Bind();
        void UnBind();
        void setVertexLayout(VertexLayOut layout);

    private:
        unsigned int m_vao;
    };

}// namespace Agate
#endif//AGATE_VERTEXARRAY_H
