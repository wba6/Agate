#include "AssimpLoader.h"
#include "Agate/Core/Logger.h"
#include "OpenGl/Texture.h"
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <future>
#include <string>

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

std::vector<Texture> AssimpLoader::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName,
                                                        std::string directory, std::vector<Texture>& textureCache) {

    std::vector<Texture> textures;
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;
        for (auto &j: textureCache) {
            if (std::strcmp(j.getPath().data(), str.C_Str()) == 0) {
                textures.push_back(j);
                skip = true;
                break;
            }
        }
        if (!skip) {
            Texture texture(str.C_Str(), directory);
            texture.setType(typeName);
            textures.push_back(texture);
            textureCache.push_back(texture);
        }
    }
    return std::move(textures);
}

} // namespace Agate
