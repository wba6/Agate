/**
 * @brief Include file for the AssimpLoader class
 * 
 * Hides assimp's implementation details from the rest of the
 * engine in order to protect against unintended usage of the
 * library
 */

#ifndef AGATE_ASSIMPLOADER_H
#define AGATE_ASSIMPLOADER_H

#include <future>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace Agate {

struct AssimpLoaderImpl;

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

    /**
     * @brief Imports a model from a file as an assimp scene
     * 
     * @param path Path to the model file
     * @param flags Post-processing flags for Assimp::Importer::ReadFile
     * @return Assimp scene with model data
     */
    std::future<const aiScene*> readFile(const std::string& path, unsigned int flags);

private:
    Assimp::Importer importer;
};

} // namespace Agate

#endif // AGATE_ASSIMPLOADER_H
