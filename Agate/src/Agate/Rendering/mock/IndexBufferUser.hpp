#ifndef AGATE_INDEXBUFFERUSER_HPP
#define AGATE_INDEXBUFFERUSER_HPP

#include "Agate/Rendering/UUID.hpp"
#include <vector>

namespace Agate {

    /**
     * @brief A mock representation of an OpenGL Index Buffer for use on the main thread.
     *
     * IndexBufferUser stores the index data and associated metadata (UUIDs)
     * to allow the application to interact with index buffers without
     * directly making OpenGL calls.
     */
    class IndexBufferUser {
    public:
        /**
         * @brief Constructs an IndexBufferUser.
         *
         * @param vector The index data.
         * @param VAOUUID The UUID of the Vertex Array this index buffer is attached to.
         */
        explicit IndexBufferUser(std::vector<unsigned int> &vector, UUID VAOUUID);

        // Disable copying
        IndexBufferUser(const IndexBufferUser&) = delete;
        IndexBufferUser& operator=(const IndexBufferUser&) = delete;

        // Enable move semantics
        IndexBufferUser(IndexBufferUser&& other) noexcept;
        IndexBufferUser& operator=(IndexBufferUser&& other) noexcept;

        /**
         * @brief Destroys the IndexBufferUser.
         */
        ~IndexBufferUser();

        /**
         * @brief Gets the index data.
         * @return A reference to the vector of indices.
         */
        std::vector<unsigned int>& getIndinces() { return m_indinces;};

        /**
         * @brief Gets the index data.
         * @return A const reference to the vector of indices.
         */
        const std::vector<unsigned int>& getIndinces() const { return m_indinces;};

        /**
         * @brief Gets the UUID of this Index Buffer.
         * @return The UUID of the index buffer.
         */
        UUID getUUID() const { return m_UUID;}

        /**
         * @brief Gets the UUID of the attached Vertex Array.
         * @return The UUID of the attached Vertex Array.
         */
        UUID getAttachedVAOUUID() const { return m_VAOUUID;};

        /**
         * @brief Binds the index buffer.
         *
         * Enqueues a command to bind the underlying OpenGL index buffer.
         */
        void Bind() const;

        /**
         * @brief Unbinds the index buffer.
         *
         * Enqueues a command to unbind the underlying OpenGL index buffer.
         */
        void UnBind() const;

        /**
         * @brief Gets the number of indices in the buffer.
         * @return The number of indices.
         */
        unsigned int GetNumOfIndices() const;

    private:
        std::vector<unsigned int> m_indinces;
        UUID m_VAOUUID;
        UUID m_UUID;
    };

}// namespace Agate

#endif//AGATE_INDEXBUFFERUSER_HPP
