/**
 * @brief Include file for the AssimpLoader class
 * 
 * Hides assimp's implementation details from the rest of the
 * engine in order to protect against unintended usage of the
 * library
 */

#ifndef AGATE_ASSIMPLOADER_H
#define AGATE_ASSIMPLOADER_H

namespace Agate {

/**
 * @brief Wraps calls to assimp and decouples assimp implementation
 *        details from the engine
 */
class AssimpLoader {
public:

    /**
     * @brief Default constructor
     */
    AssimpLoader() = default;

    /**
     * @brief Builds flags for import post-processing options
     * 
     * @param flipUVs If true, include aiProcess_FlipUVs. Default false
     * @return Bitmask representing the post-processing flags
     */
    unsigned int getFlags(bool flipUVs = false) const;
};

} // namespace Agate

#endif // AGATE_ASSIMPLOADER_H
