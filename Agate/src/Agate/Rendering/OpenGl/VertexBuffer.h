//
// Created by TANK1_41 on 9/16/2022.
//

#ifndef AGATE_VERTEXBUFFER_H
#define AGATE_VERTEXBUFFER_H

#include "BufferLayout.h"

#define STREAM_DRAW 0x88E0
#define STREAM_READ 0x88E1
#define STREAM_COPY 0x88E2
#define STATIC_DRAW 0x88E4
#define STATIC_READ 0x88E5
#define STATIC_COPY 0x88E6
#define DYNAMIC_DRAW 0x88E8
#define DYNAMIC_READ 0x88E9
#define DYNAMIC_COPY 0x88EA
namespace Agate {

    class VertexBuffer {
    public:
        /**
         * Constructor creates a vertex buffer
         * @param vertices
         * @param drawtype
         * @param data_size
         */
        explicit VertexBuffer(const void *vertices, int32_t drawtype, size_t data_size);

        void Bind();

        void UnBind();

    private:
        unsigned int m_vbo;
    };
}// namespace Agate


#endif//AGATE_VERTEXBUFFER_H
