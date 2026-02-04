#include "AssimpLoader.h"
#include "Agate/Core/Logger.h"
#include <assimp/postprocess.h>

namespace Agate {

unsigned int AssimpLoader::getFlags(bool flipUVs) const {

    // default flags
    unsigned int assimpFlags = aiProcess_CalcTangentSpace     |
                            aiProcess_Triangulate             |
                            aiProcess_JoinIdenticalVertices   |
                            aiProcess_SortByPType;

    // option flipUVs
    if(flipUVs) {
        assimpFlags |= aiProcess_FlipUVs;
    }

    return assimpFlags;
}

std::future<const aiScene*> AssimpLoader::readFile(const std::string& path, unsigned int flags) {

    return std::async(std::launch::async, [this, path, flags]() {

        const aiScene* scene = importer.ReadFile(path, flags);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            PRINTERROR("ASSIMP ERROR: {}", importer.GetErrorString());
            return static_cast<const aiScene*>(nullptr);
        }

        return scene;
    });
}

} // namespace Agate
