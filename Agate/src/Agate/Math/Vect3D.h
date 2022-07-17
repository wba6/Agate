#pragma once
#include "Execptions.h"

namespace Agate
{
    struct Vec3D {
        float x, y, z;

        Vec3D() = default;

        Vec3D(float x_cord, float y_cord, float z_cord)
            : x(x_cord), y(y_cord), z(z_cord)
        {}


        float &operator[](int i)
        {
            if (i < 3)
                return ((&x)[i]);
            else
                throw OutOfBonds();
        }

        const float &operator[](int i) const
        {
            if (i < 3)
                return ((&x)[i]);
            else
                throw OutOfBonds();
        }
    };


}// namespace Agate
