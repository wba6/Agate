#pragma once
#include "Execptions.h"

namespace Agate
{
    struct Vec2D {
        float x, y;

        Vec2D() = default;

        Vec2D(float x_cord, float y_cord)
            : x(x_cord), y(y_cord)
        {}


        float &operator[](int i)
        {
            if (i < 2)
                return ((&x)[i]);
            else
                throw OutOfBonds();
        }

        const float &operator[](int i) const
        {
            if (i < 2)
                return ((&x)[i]);
            else
                throw OutOfBonds();
        }
    };
}// namespace Agate
