#include "UUID.hpp"
#include <random>

namespace Agate {
    static std::random_device s_RandomDevice;
    static std::mt19937_64 s_Engine(s_RandomDevice());
    static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

    // Initializes to 0 (Null UUID)
    UUID::UUID()
        : m_UUID(0)
    {
    }

    // Generate a new random ID
    UUID UUID::Generate()
    {
        uint64_t id = s_UniformDistribution(s_Engine);
        // Ensure we don't accidentally generate a null UUID (highly unlikely but possible)
        while (id == 0) {
            id = s_UniformDistribution(s_Engine);
        }
        return UUID(id);
    }

    // Assign an explicit ID
    UUID::UUID(uint64_t uuid)
        : m_UUID(uuid)
    {
    }

}
