#ifndef AGATE_INDEXBUFFERUSER_HPP
#define AGATE_INDEXBUFFERUSER_HPP

#include "Rendering/UUID.hpp"
#include <vector>

namespace Agate {

    class IndexBufferUser {
    public:
        explicit IndexBufferUser(std::vector<unsigned int> &vector, UUID VAOUUID)
            : m_indinces(vector), m_VAOUUID(VAOUUID){};

        ~IndexBufferUser();

        std::vector<unsigned int>& getIndinces() { return m_indinces;};
        size_t getUUID() { return m_UUID;}
        UUID getAttachedVAOUUID() { return m_VAOUUID;};


        //void Bind();

        //void UnBind();

        //[[nodiscard]] unsigned int GetNumOfIndices() const;

        /**
         * SetUpBuffer is ment to set up the index buffer within a vertex array
         * Before calling insure index buffer is bound
         * After calling insure that you unbind the vertex array before unbinding index buffer
         * this function does not unbind the index buffer
         */
        //void setUpBuffer();

    private:
        std::vector<unsigned int> m_indinces;
        UUID m_VAOUUID;
        UUID m_UUID;
    };

}// namespace Agate

#endif//AGATE_INDEXBUFFERUSER_HPP
