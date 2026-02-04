#include "AssimpLoader.h"
#include "assimp/postprocess.h"

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

} // namespace Agate
