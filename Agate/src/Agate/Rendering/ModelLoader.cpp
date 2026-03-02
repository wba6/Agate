#include "agpch.h"
#include "ModelLoader.h"
#include "AssimpLoader.h"
#include "Mesh.h"
#include "ModelEditor.h"
#include <utility>
#include <memory>

namespace fs = std::filesystem;

Agate::ModelLoader::~ModelLoader() = default;

Agate::ModelLoader::ModelLoader(std::string const &path)
    : m_directory(extractDirectory(path)), m_path(path) {}

std::future<std::unique_ptr<Agate::ModelEditor>> Agate::ModelLoader::LoadModel(const std::string &path) {

    return std::async(std::launch::async, [path]() {

        std::unique_ptr<Agate::ModelLoader> loader = std::make_unique<Agate::AssimpLoader>(path);
        
        if (!loader->loadModel()) {
            PRINTWARN("Failed to load model from {}", path);

            return std::unique_ptr<Agate::ModelEditor>(nullptr);
        }
        loader->m_meshes = loader->parseModel();

        return std::make_unique<Agate::ModelEditor>(std::move(loader->m_path), std::move(loader->m_meshes));
    });
}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
