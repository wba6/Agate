#ifndef AGATE_MODELLOADER_H
#define AGATE_MODELLOADER_H

#include "Agate/Async/TaskPool.h"
#include "Mesh.h"
#include "ModelEditor.h"
#include "OpenGl/Shader.h"
#include "OpenGl/Texture.h"
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

        /**
         * @brief Destructor - Blocks and waits for future completion if necessary
         */
        virtual ~ModelLoader();

        /**
         * @brief Instructs the loader to start internally loading its model
         * 
         * @param path Path to the model file
         */
        static TaskHandle<ModelEditor> LoadModel(std::string const &path);

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
         * 
         * @return Operation status
         * @retval true Success
         * @retval false Failure
         */
        virtual bool loadModel() = 0;

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
