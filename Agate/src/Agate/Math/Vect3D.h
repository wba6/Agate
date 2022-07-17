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

        Vec3D &operator*=(float s)
        {
            x *s;
            y *s;
            z *s;

            return *this;
        }

        Vec3D &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;
            z *= s;

            return *this;
        }
    };

    inline Vec3D operator*(const Vec3D &vec, float s)
    {
        return (Vec3D(vec.x * s, vec.y * s, vec.z * s));
    }

    inline Vec3D operator/(const Vec3D &vec, float s)
    {
        s = 1.0f / s;
        return (Vec3D(vec.x * s, vec.y * s, vec.z * s));
    }

    inline Vec3D operator-(const Vec3D &vec)
    {
        return (Vec3D(-vec.x, -vec.y, -vec.z));
    }

    inline float Magnitude(const Vec3D &vec)
    {
        return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
    }

    inline Vec3D Normalize(const Vec3D &vec)
    {
        return (vec / Magnitude(vec));
    }

}// namespace Agate
