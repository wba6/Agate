#ifndef AGATE_MODELLOADER_H
#define AGATE_MODELLOADER_H

#include "Mesh.h"
#include "ModelEditor.h"
#include "OpenGl/Shader.h"
#include "OpenGl/Texture.h"
#include <future>
#include <memory>

#define MAX_BONE_INFLUENCE 4

namespace Agate {

    class ModelLoader {
    public:
        // model data
        std::vector<Texture> m_texturesLoaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::string m_path;
        ModelEditor m_model;

        /**
         * @brief Destructor - Blocks and waits for future completion if necessary
         */
        virtual ~ModelLoader();

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
        * 
        * @warning If `ModelLoader::LoadModel` has not been invoked, this method will
        *          never do anything
        */
        void Draw(Shader &shader);

        /**
         * @brief Instructs the loader to start internally loading its model
         * 
         * @param path Path to the model file
         */
        static std::future<std::unique_ptr<ModelEditor>> LoadModel(std::string const &path);

protected:

        /**
         * @brief Construct a ModelLoader and start loading a model on a background task.
         *
         * Initializes model metadata and launches an asynchronous Assimp import using
         * std::async. The returned aiScene* is stored in a std::future so the caller
         * can continue without blocking.
         *
         * @param path     Filesystem path to the model file.
         *
         * @note The actual GPU/engine-side preparation is deferred until Draw() observes
         *       the future is ready and calls prepareScene().
         */ 
        ModelLoader(std::string const &path);

        /**
         * @brief Performs the I/O part of loading the model
         */
        virtual void loadModel() = 0;

        /**
         * @brief Parses the loaded model into a form that the engine can render
         * 
         * @return Parsed meshes
         */
        virtual std::vector<Mesh> parseModel() = 0;

    private:

        //helper function
        std::string extractDirectory(const std::string& path);
    };
}

#endif //AGATE_MODELLOADER_H
