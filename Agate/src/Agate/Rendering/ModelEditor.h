/**
 * @brief Include file for the ModelEditor class
 * 
 * Handles internal model representation and allows editing of
 * the base model in the editor (before sending to the renderer)
 */

#ifndef AGATE_MODELEDITOR_H
#define AGATE_MODELEDITOR_H

#include "Mesh.h"
#include "OpenGl/Shader.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Agate {

struct Transform {
    Transform();
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
};

class ModelEditor {
private:
    std::string m_path;
    std::vector<Mesh> m_meshes;
    Transform m_transform;
public:

    /**
     * @brief Default constructor
     */
    ModelEditor() = default;

    /**
     * @brief Constructor - initializes with given meshes and path
     * 
     * @param path Path to the source file of this model
     * @param meshes Mesh data for this model
     */
    ModelEditor(std::string path, std::vector<Mesh> meshes);

    /**
     * @brief Draws the underlying model
     * 
     * @param shader Shader to use when drawing
     */
    void Draw(Shader& shader);
};
} // namespace Agate

#endif // AGATE_MODELEDITOR_H
