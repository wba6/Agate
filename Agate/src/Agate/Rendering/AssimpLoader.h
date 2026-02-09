/**
 * @brief Include file for the AssimpLoader class
 * 
 * Hides assimp's implementation details from the rest of the
 * engine in order to protect against unintended usage of the
 * library
 */

#ifndef AGATE_ASSIMPLOADER_H
#define AGATE_ASSIMPLOADER_H

#include "OpenGl/Texture.h"
#include <future>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

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

    /**
     * @brief Imports a model from a file as an assimp scene
     * 
     * @param path Path to the model file
     * @param flags Post-processing flags for Assimp::Importer::ReadFile
     * @return Assimp scene with model data
     */
    std::future<const aiScene*> readFile(const std::string& path, unsigned int flags);

    /**
     * @brief Loads textures required for this material
     * 
     * @param material Material to load textures for
     * @param type Type of textures to load
     * @param typeName Name for the type of textures to load
     * @param directory Directory of source model file
     * @param textureCache Cache of previously loaded textures
     * 
     * @return Textures required by this material
     */
    std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName, std::string directory, std::vector<Texture>& textureCache);

private:
    Assimp::Importer importer;
};

} // namespace Agate

#endif // AGATE_ASSIMPLOADER_H
