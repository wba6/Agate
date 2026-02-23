#include "agpch.h"
#include "ModelLoader.h"
#include "AssimpLoader.h"
#include "Mesh.h"
#include "ModelEditor.h"
#include <utility>
#include <memory>

namespace fs = std::filesystem;

Agate::ModelLoader::~ModelLoader() {

    // Block until asynchronous load is finished, if applicable
    if (m_futureScene.valid()) {
        m_futureScene.wait();
    }
}

Agate::ModelLoader::ModelLoader(std::string const &path)
    : m_directory(extractDirectory(path)), m_path(path) {}

void Agate::ModelLoader::Draw(Agate::Shader &shader) {

    // Once we get the scene we prepare it, i.e once we get the futures value we use it 
    // once used it is no longer valid i.e this if is skipped
    if (m_futureScene.valid()) {
        auto status = m_futureScene.wait_for(std::chrono::seconds(0));
        if (status == std::future_status::ready) {
            // Once this is done the future scene will no longer be valid
            if (m_futureScene.get()) {
                m_meshes = parseModel();
                m_model = Agate::ModelEditor(m_path, m_meshes);
            } else {
                PRINTWARN("ModelLoader: Model load failed");
            }
        }
    }

    m_model.Draw(shader);
}

std::future<std::unique_ptr<Agate::ModelLoader>> Agate::ModelLoader::LoadModel(const std::string &path) {

    return std::async(std::launch::async, [path]() {

        std::unique_ptr<Agate::ModelLoader> loader = std::make_unique<AssimpLoader>(path);
        loader->m_futureScene = loader->loadModel();

        loader->m_futureScene.wait();
        if (loader->m_futureScene.get()) {
            loader->m_meshes = loader->parseModel();
            loader->m_model = Agate::ModelEditor(loader->m_path, loader->m_meshes);
        } else {
            PRINTWARN("ModelLoader: Model load failed");
        }

        return loader;
    });

}

std::string Agate::ModelLoader::extractDirectory(const std::string &path) {
    fs::path p(path);
    return p.parent_path().generic_string();
}
