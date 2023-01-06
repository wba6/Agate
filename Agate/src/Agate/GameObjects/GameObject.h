//
// Created by William Aey on 10/23/2022.
//

#pragma once

#include "Agate/Rendering/Camera.h"

enum GameObjectType {
    Square,
    Triangle
};

namespace Agate
{
    class GameObject {
    public:
        explicit GameObject(int x, int y, float rotation) : x(x), y(y), rotation(rotation){};

        virtual void Render() = 0;
        virtual void setXPos(int xPos) = 0;
        virtual void setYPos(int yPos) = 0;
        virtual GameObjectType GetObjectType() = 0;
        virtual std::string GetObjectString() = 0;
        virtual int GetInstanceNumber() { return instanceNumber; }
        virtual ~GameObject()
        {
            delete camera;
        }

        float x, y;
        float rotation;
        int instanceNumber;
        Camera *camera;
    };
}// namespace Agate