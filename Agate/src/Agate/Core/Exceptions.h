#ifndef AGATE_EXCEPTIONS_H
#define AGATE_EXCEPTIONS_H

#include <exception>
#include <string>
#include "Agate/Rendering/UUID.hpp"

namespace Agate {

    class UUIDNotFoundException : public std::exception {
    public:
        UUIDNotFoundException(const UUID& uuid, const std::string& type)
            : m_UUID(uuid), m_Type(type) {
            m_Message = "UUID not found: " + std::to_string((uint64_t)m_UUID) + " for type " + m_Type;
        }

        const char* what() const noexcept override {
            return m_Message.c_str();
        }

    private:
        UUID m_UUID;
        std::string m_Type;
        std::string m_Message;
    };

}

#endif // AGATE_EXCEPTIONS_H
