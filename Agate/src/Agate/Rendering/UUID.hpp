#ifndef AGATE_UUID_HPP
#define AGATE_UUID_HPP

#include <cstdint>
#include <functional>

namespace Agate {

    class UUID {
    public:
        UUID(); // Generates a completely new random 64-bit ID
        UUID(uint64_t uuid); // Constructs from an existing ID
        UUID(const UUID&) = default; // Allow copying

        // Implicit conversion to uint64_t 
        operator uint64_t() const { return m_UUID; }

    private:
        uint64_t m_UUID;
    };

}

// std::hash Specialization 
namespace std {
    template<>
    struct hash<Agate::UUID> {
        std::size_t operator()(const Agate::UUID& uuid) const {
            return (uint64_t)uuid;
        }
    };
}

#endif // AGATE_UUID_HPP
