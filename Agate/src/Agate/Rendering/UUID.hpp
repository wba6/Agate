#ifndef AGATE_UUID_HPP
#define AGATE_UUID_HPP

#include <cstdint>
#include <functional>

namespace Agate {

    class UUID {
    public:
        UUID(); // Initializes to 0 (Null UUID)
        static UUID Generate(); // Generates a completely new random 64-bit ID
        UUID(uint64_t uuid); // Constructs from an existing ID
        UUID(const UUID&) = default; // Allow copying
        UUID& operator=(const UUID&) = default; // Allow assignment

        // Explicit conversion to uint64_t 
        uint64_t Get() const { return m_UUID; }

        // Check if the UUID is valid (not 0)
        operator bool() const { return m_UUID != 0; }

        bool operator==(const UUID& other) const {
            return m_UUID == other.m_UUID;
        }

        bool operator!=(const UUID& other) const {
            return m_UUID != other.m_UUID;
        }

    private:
        uint64_t m_UUID;
    };

}

// std::hash Specialization 
namespace std {
    template<>
    struct hash<Agate::UUID> {
        std::size_t operator()(const Agate::UUID& uuid) const {
            return uuid.Get();
        }
    };
}

#endif // AGATE_UUID_HPP
