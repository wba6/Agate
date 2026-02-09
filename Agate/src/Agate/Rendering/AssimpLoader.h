/**
 * @brief Include file for the AssimpLoader class
 * 
 * Hides assimp's implementation details from the rest of the
 * engine in order to protect against unintended usage of the
 * library
 */

#ifndef AGATE_ASSIMPLOADER_H
#define AGATE_ASSIMPLOADER_H

#include "Mesh.h"
#include "OpenGl/Texture.h"
#include <future>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <glm/glm.hpp>

namespace Agate {

/**
 * @brief Wraps calls to assimp and decouples assimp implementation
 *        details from the engine
 */
class AssimpLoader {
public:

    /**
     * @brief Constructor
     * 
     * @param directory Directory where the model is located
     */
    AssimpLoader(std::string directory);

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
    * @brief Convert a loaded Assimp scene into engine-ready mesh data.
    *
    * Validates the imported scene and recursively processes the node hierarchy to
    * populate this loader's mesh list.
    *
    * @param scene Scene produced by Assimp::Importer::ReadFile()
    * @param path
    * @param textureCache
    *
    * @warning Potentially expensive: performs vertex/index extraction and may
    *          trigger GPU buffer uploads depending on your Mesh implementation.
    *          Intended to be called once, after the async import completes.
    */
    std::vector<Mesh> prepareScene(const aiScene *scene, std::string path, std::vector<Texture>& textureCache);

    /**
     * @brief Recursively processes a node and its children, parsing out
     *        all contained meshes
     * 
     * @param node Current node to process
     * @param scene Scene containing the node
     * @param transform Transformation matrix of the current node relative to
     *                  the scene origin
     * @param textureCache Cache of previously loaded textures
     * 
     * @return Parsed meshes
     */
    std::vector<Mesh> processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform, std::vector<Texture>& textureCache);

    /**
     * @brief Parses a Mesh out of an assimp scene
     * 
     * @param mesh Assimp representation of the mesh
     * @param scene Assimp scene containing the mesh
     * @param transform Local transformation of the mesh within the scene
     * @param textureCache Cache of previously loaded textures
     * 
     * @return Parsed mesh
     */
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, const glm::mat4 &transform, std::vector<Texture>& textureCache);

    /**
     * @brief Loads textures required for this material
     * 
     * @param material Material to load textures for
     * @param type Type of textures to load
     * @param typeName Name for the type of textures to load
     * @param textureCache Cache of previously loaded textures
     * 
     * @return Textures required by this material
     */
    std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName, std::vector<Texture>& textureCache);

private:
    Assimp::Importer importer;
    std::string directory;
};

} // namespace Agate

#endif // AGATE_ASSIMPLOADER_H
