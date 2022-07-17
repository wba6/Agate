#pragma once
namespace Agate
{
    struct Vec3D {
        float x, y, z;

        Vec3D() = default;

        Vec3D(float x_cord, float y_cord, float z_cord)
            : x(x_cord), y(y_cord), z(z_cord)
        {}


        //TODO: Not memory safe fix!
        float &operator[](int i)
        {
            return ((&x)[i]);
        }

        const float &operator[](int i) const
        {
            return ((&x)[i]);
        }
    };

}// namespace Agate
