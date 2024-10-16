//
// Created by William Aey on 10/17/2022.
//

#ifndef AGATE_INDEXBUFFER_H
#define AGATE_INDEXBUFFER_H

#include "VertexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace Agate {

    class IndexBuffer {
    public:
        explicit IndexBuffer(std::vector<unsigned int> &vector);

        ~IndexBuffer();

        void Bind();

        void UnBind();

        [[nodiscard]] unsigned int GetNumOfIndices() const;

        /**
         * SetUpBuffer is ment to set up the index buffer within a vertex array
         * Before calling insure index buffer is bound
         * After calling insure that you unbind the vertex array before unbinding index buffer
         * this function does not unbind the index buffer
         */
        void setUpBuffer();

    private:
        std::vector<unsigned int> m_indinces;
        unsigned int m_ibo;
    };

}// namespace Agate

#endif//AGATE_INDEXBUFFER_H
