#ifndef AGATE_MODELLOADER_H
#define AGATE_MODELLOADER_H

#include "AssimpLoader.h"
#include "Mesh.h"
#include "OpenGl/Shader.h"
#include "OpenGl/Texture.h"
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <future>

#define MAX_BONE_INFLUENCE 4

namespace Agate {

    class ModelLoader {
    public:
        // model data
        std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::string m_path;

        /**
         * @brief Construct a ModelLoader and start loading a model on a background task.
         *
         * Initializes model metadata and launches an asynchronous Assimp import using
         * std::async. The returned aiScene* is stored in a std::future so the caller
         * can continue without blocking.
         *
         * @param path     Filesystem path to the model file.
         * @param gamma    Enable/disable gamma correction for textures.
         * @param flipUVs  If true, flip UV coordinates vertically during import.
         *
         * @note The actual GPU/engine-side preparation is deferred until Draw() observes
         *       the future is ready and calls prepareScene().
         */ 
        ModelLoader(std::string const &path, bool flipUVs = false);

        /**
        * @brief Render the model; finalize loading when the async import completes.
        *
        * Each frame, this function polls the async import future. When the import
        * completes, it performs one-time scene preparation (node traversal, mesh
        * extraction, and any associated buffer creation) by calling prepareScene().
        * After preparation, it draws all loaded meshes.
        *
        * @param shader Shader program used to render the meshes.
        *
        * @note Non-blocking: if the import is not ready yet, this function only draws
        *       meshes that have already been prepared (often none).
        */
        void Draw(Shader &shader);


    private:
        
        /**
         * @brief The AssimpLoader is kept as a class member in order to preserve the
         *        lifetimes of objects managed by assimp
         */
        AssimpLoader assimp;

        /**
         * @brief A future for the loaded model is kept as a class member to preserve
         *        access to the result of the asynchronous load task
         */
        std::future<const aiScene*> m_futureScene;

    private:

        /**
        * @brief Convert a loaded Assimp scene into engine-ready mesh data.
        *
        * Validates the imported scene and recursively processes the node hierarchy to
        * populate this loader's mesh list.
        *
        * @param scene Scene produced by Assimp::Importer::ReadFile().
        *
        * @warning Potentially expensive: performs vertex/index extraction and may
        *          trigger GPU buffer uploads depending on your Mesh implementation.
        *          Intended to be called once, after the async import completes.
        */
        void prepareScene(const aiScene *scene);

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode *node, const aiScene *scene, const glm::mat4 &parentTransform);

        Mesh processMesh(aiMesh *mesh, const aiScene *scene, const glm::mat4 &transform);

        //helper function
        std::string extractDirectory(const std::string& path);
    };
}

#endif //AGATE_MODELLOADER_H
