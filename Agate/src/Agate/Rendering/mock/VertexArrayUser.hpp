
#ifndef AGATE_VERTEXARRAYUSER_HPP
#define AGATE_VERTEXARRAYUSER_HPP

#include "../OpenGl/BufferLayout.h"
#include "IndexBufferUser.hpp"
#include "Agate/Rendering/UUID.hpp"
#include <cstddef>
#include <memory>

namespace Agate {
    class VertexArrayUser {
    public:
        //takes in a data layout and the data through a void pointer
        VertexArrayUser(BufferDataLayout bufferInformation, std::shared_ptr<void> data, size_t data_size);

        BufferDataLayout getBufferData() {return m_bufferInformation;};
        std::shared_ptr<void>  getData() {return m_data;};
        size_t getDataSize() { return m_dataSize;}
        UUID getUUID() { return m_UUID;}

        /**
         * Adds index buffer to the vertex array
         * @param indexBuffer
         */
        //void addIndexBuffer(IndexBufferUser indexBuffer);

        void Bind() const;

        void UnBind() const;

        virtual ~VertexArrayUser() = default;

    private:
        UUID m_UUID;
        BufferDataLayout m_bufferInformation;
        std::shared_ptr<void> m_data;
        size_t m_dataSize;
    };

}// namespace Agate
#endif//AGATE_VERTEXARRAYUSER_H
