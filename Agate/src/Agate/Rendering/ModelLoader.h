#ifndef AGATE_MODELLOADER_H
#define AGATE_MODELLOADER_H

#include "Agate/Async/TaskPool.h"
#include "Mesh.h"
#include "ModelEditor.h"
#include "mock/ShaderUser.hpp"
#include "mock/TextureUser.hpp"
#include <future>
#include <memory>

#define MAX_BONE_INFLUENCE 4

namespace Agate {

    class ModelLoader {
    public:
        // model data
        std::vector<TextureUser> m_texturesLoaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> m_meshes;
        std::string m_directory;
        std::string m_path;

        /**
         * @brief Destructor - Blocks and waits for completion if necessary
         */
        virtual ~ModelLoader();

        /**
         * @brief Enqueues a task to load this loader's target and parses it into
         *        an engine-ready format
         * 
         * @param path Path to the model file
         * @param flipUVs If true, flip UV coordinates during post-processing
         */
        static TaskHandle<ModelEditor> LoadModel(std::string const &path, bool flipUVs = false);

protected:

        /**
         * @brief Construct a ModelLoader for a target model file
         *
         * @param path Filesystem path to the model file
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
