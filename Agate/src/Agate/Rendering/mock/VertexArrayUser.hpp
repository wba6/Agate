
#ifndef AGATE_VERTEXARRAYUSER_HPP
#define AGATE_VERTEXARRAYUSER_HPP

#include "../OpenGl/BufferLayout.h"
#include "IndexBufferUser.hpp"
#include "Agate/Rendering/UUID.hpp"
#include <cstddef>
#include <memory>

namespace Agate {
    /**
     * @brief A mock representation of an OpenGL Vertex Array for use on the main thread.
     *
     * VertexArrayUser stores vertex buffer layout and data on the main thread
     * to allow the application to interact with vertex arrays without
     * directly making OpenGL calls.
     */
    class VertexArrayUser {
    public:
        /**
         * @brief Constructs a VertexArrayUser.
         *
         * @param bufferInformation The layout of the vertex buffer data.
         * @param data A shared pointer to the vertex buffer data.
         * @param data_size The size of the vertex buffer data in bytes.
         */
        VertexArrayUser(BufferDataLayout bufferInformation, std::shared_ptr<void> data, size_t data_size);

        /**
         * @brief Gets the vertex buffer data layout.
         * @return The buffer data layout.
         */
        BufferDataLayout getBufferData() {return m_bufferInformation;};

        /**
         * @brief Gets the vertex buffer data.
         * @return A shared pointer to the data.
         */
        std::shared_ptr<void>  getData() {return m_data;};

        /**
         * @brief Gets the size of the vertex buffer data.
         * @return The data size in bytes.
         */
        size_t getDataSize() { return m_dataSize;}

        /**
         * @brief Gets the UUID of this Vertex Array.
         * @return The UUID of the vertex array.
         */
        UUID getUUID() { return m_UUID;}

        /**
         * @brief Binds the vertex array.
         *
         * Enqueues a command to bind the underlying OpenGL vertex array.
         */
        void Bind() const;

        /**
         * @brief Unbinds the vertex array.
         *
         * Enqueues a command to unbind the underlying OpenGL vertex array.
         */
        void UnBind() const;

        /**
         * @brief Virtual destructor for VertexArrayUser.
         */
        virtual ~VertexArrayUser() = default;

    private:
        UUID m_UUID;
        BufferDataLayout m_bufferInformation;
        std::shared_ptr<void> m_data;
        size_t m_dataSize;
    };

}// namespace Agate
#endif//AGATE_VERTEXARRAYUSER_H
