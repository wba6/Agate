//
// Created by TANK1_41 on 9/16/2022.
//

#ifndef AGATE_VERTEXBUFFER_H
#define AGATE_VERTEXBUFFER_H


struct DrawTypes {
    static int8_t STREAM_DRAW;
    static int8_t STREAM_READ;
    static int8_t STREAM_COPY;
    static int8_t STATIC_DRAW;
    static int8_t STATIC_READ;
    static int8_t STATIC_COPY;
    static int8_t DYNAMIC_DRAW;
    static int8_t DYNAMIC_READ;
    static int8_t DYNAMIC_COPY;
};

class VertexBuffer {
public:
    VertexBuffer(float *data, size_t dataSize, int8_t drawtype);
    void Bind();
    void UnBind();

private:
    unsigned int m_vbo;
};


#endif//AGATE_VERTEXBUFFER_H
