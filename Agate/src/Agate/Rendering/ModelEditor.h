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

    /**
     * @brief Rotates the model about an axis
     * 
     * @param radians Amount to rotate by, in radians
     * @param axis Normalized vector along the axis to rotate about
     */
    void Rotate(glm::f32 radians, glm::vec3 axis);

    /**
     * @brief Sets the models rotation, ignoring current rotation
     * 
     * @param radians Amount model should be rotated, in radians
     * @param axis Normalized vector along the axis to rotate about
     */
    void SetRotation(glm::f32 radians, glm::vec3 axis);

    /**
     * @brief Moves the position of the model
     * 
     * @param translation Vector to add to the model's current position
     */
    void Translate(glm::vec3 translation);

    /**
     * @brief Sets the position of the model relative to its local
     *        origin
     * 
     * @param position Position vector for the model
     */
    void SetPosition(glm::vec3 position);

    /**
     * @brief Resizes the model by a scalar vector
     * 
     * @param scalar Scalar vector with a multiplier for each axis
     */
    void Scale(glm::vec3 scalar);

    /**
     * @brief Sets the model's size to a scalar of its original size
     * 
     * @param scalar Scalar vector with a multiplier for each axis
     */
    void SetScale(glm::vec3 scalar);
};
} // namespace Agate

#endif // AGATE_MODELEDITOR_H
