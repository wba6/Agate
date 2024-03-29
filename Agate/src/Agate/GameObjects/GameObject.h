//
// Created by William Aey on 10/23/2022.
//

#pragma once

#include "Agate/Rendering/Camera.h"
#include "Agate/Rendering/OpenGl/IndexBuffer.h"
#include "Agate/Rendering/OpenGl/Shader.h"
#include "Agate/Rendering/OpenGl/VertexArray.h"
#include "Agate/Rendering/OpenGl/VertexBuffer.h"
#include "GameObjectUI/GameObjectsUI.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
enum GameObjectType {
    Square,
    Triangle,
    Light,
    Cube
};

namespace Agate
{
    class GameObject {
    public:
        explicit GameObject(float X = 0, float Y = 0, float Z = 0, float rotation = 0)
            : x(X), y(Y), z(Z), rotation(rotation), color(0){};

        virtual void Render() = 0;
        virtual void setXPos(float xPos) { x = xPos; };
        virtual void setYPos(float yPos) { y = yPos; };
        virtual void setZPos(float zPos) { z = zPos; };
        virtual GameObjectType GetObjectType() = 0;
        virtual std::string GetObjectString() = 0;
        virtual int GetInstanceNumber() { return instanceNumber; }
        virtual ~GameObject()
        {
            delete camera;
        }
        glm::vec4 color;
        float x, y, z;
        float rotation;
        int instanceNumber;
        Camera *camera;
    };
}// namespace Agate