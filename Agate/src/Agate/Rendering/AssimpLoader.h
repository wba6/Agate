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
#include "ModelLoader.h"
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
class AssimpLoader : public ModelLoader {
public:

    /**
     * @brief Constructor
     * 
     * @param path Path to the model file
     * @param flipUVs If true, include aiProcess_FlipUVs for postprocessing.
     *                Default false
     */
    AssimpLoader(const std::string& path, bool flipUVs = false);

    virtual ~AssimpLoader() override;

protected:

    /**
     * @brief Performs the I/O part of loading the model
     * 
     * @return Operation status
     * @retval true Success
     * @retval false Failure
     */
    virtual bool loadModel() final override;

    /**
     * @brief Parses the loaded model into a form that the engine can render
     * 
     * @return Parsed meshes
     */
    virtual std::vector<Mesh> parseModel() final override;

private:
    Assimp::Importer m_importer;
    bool m_flipUVs;
    const aiScene* m_scene;

    /**
     * @brief Recursively processes a node and its children, parsing out
     *        all contained meshes
     * 
     * @param node Current node to process
     * @param scene Scene containing the node
     * @param transform Transformation matrix of the current node relative to
     *                  the scene origin
     * 
     * @return Parsed meshes
     */
    std::vector<Mesh> processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform);

    /**
     * @brief Parses a Mesh out of an assimp scene
     * 
     * @param mesh Assimp representation of the mesh
     * @param scene Assimp scene containing the mesh
     * @param transform Local transformation of the mesh within the scene
     * 
     * @return Parsed mesh
     */
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, const glm::mat4 &transform);

    /**
     * @brief Loads textures required for this material
     * 
     * @param material Material to load textures for
     * @param type Type of textures to load
     * @param typeName Name for the type of textures to load
     * 
     * @return Textures required by this material
     */
    std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);

    /**
     * @brief Builds flags for import post-processing options
     * 
     * @return Bitmask representing the post-processing flags
     */
    unsigned int getFlags() const;
};

} // namespace Agate

#endif // AGATE_ASSIMPLOADER_H
