//
// Created by TANK1_41 on 9/16/2022.
//

#ifndef AGATE_VERTEXARRAY_H
#define AGATE_VERTEXARRAY_H

struct VertexLayOut{
    unsigned int layoutNum;
    unsigned int vertexSize;
    bool Normilized;
    unsigned int stride;
    unsigned int offset;
};
class VertexArray {
public:
    explicit VertexArray(VertexLayOut vertexLayOut);
    void Bind();
    void UnBind();
private:
    unsigned int m_vao;
};


#endif//AGATE_VERTEXARRAY_H
