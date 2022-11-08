//
// Created by William Aey on 10/23/2022.
//

#pragma once

#include "Agate/Rendering/Camera.h"
namespace Agate{
    class GameObject {
    public:
        explicit GameObject(int x, int y, float rotation) : x(x), y(y), rotation(rotation){};

        virtual void Render() = 0;
        virtual void setXPos(int xPos) = 0;
        virtual void setYPos(int yPos) = 0;
        virtual ~GameObject()
        {
            delete camera;
        }

        int x, y;
        float rotation;
        Camera *camera;
    };
}