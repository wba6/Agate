/**
 * @brief Include file for the ModelEditor class
 * 
 * Handles internal model representation and allows editing of
 * the base model in the editor (before sending to the renderer)
 */

#ifndef AGATE_MODELEDITOR_H
#define AGATE_MODELEDITOR_H

#include "Mesh.h"
#include "mock/ShaderUser.hpp"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Agate {

/**
 * @brief Plain data struct with transformation data used to
 *        create a model matrix
 */
struct Transform {
    Transform();
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
};

/**
 * @brief Wraps a renderable model and provides mutators to
 *        edit the transformation of the model
 */
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
    void Draw(ShaderUser& shader);

    /**
     * @brief Rotates the model about an axis
     * 
     * @param radians Amount to rotate by, in radians
     * @param axis Normalized vector along the axis to rotate about
     */
    void Rotate(glm::f32 radians, const glm::vec3& axis);

    /**
     * @brief Sets the models rotation, ignoring current rotation
     * 
     * @param radians Amount model should be rotated, in radians
     * @param axis Normalized vector along the axis to rotate about
     */
    void SetRotation(glm::f32 radians, const glm::vec3& axis);

    /**
     * @brief Moves the position of the model
     * 
     * @param translation Vector to add to the model's current position
     */
    void Translate(const glm::vec3& translation);

    /**
     * @brief Sets the position of the model relative to its local
     *        origin
     * 
     * @param position Position vector for the model
     */
    void SetPosition(const glm::vec3& position);

    /**
     * @brief Resizes the model by a scalar vector
     * 
     * @param scalar Scalar vector with a multiplier for each axis
     */
    void Scale(const glm::vec3& scalar);

    /**
     * @brief Sets the model's size to a scalar of its original size
     * 
     * @param scalar Scalar vector with a multiplier for each axis
     */
    void SetScale(const glm::vec3& scalar);

    /**
     * @brief Computes the model matrix for this model using its current
     *        transform
     * 
     * The model matrix is the third component of the model-view-projection
     * rendering model and is used to convert a point from its local position
     * to its world position as defined by a translation, rotation, and
     * rescale.
     * 
     * @note The model matrix is fully computed from the transform every
     *       time this method is called
     * 
     * @return 4x4 model matrix for this model
     */
    glm::mat4 ModelMatrix() const;

    /**
     * @brief Rotation of the model as 3 angles corresponding to rotations
     *        about the X, Y, and Z axes respectively
     * 
     * @return Vector with rotations about the X, Y, and Z axes
     */
    glm::vec3 EulerAngles() const;

    /**
     * @brief Loads this model's textures into the OpenGL context
     */
    void LoadTextures();
};
} // namespace Agate

#endif // AGATE_MODELEDITOR_H
