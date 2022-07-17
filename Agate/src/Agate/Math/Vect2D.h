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

        Vec2D &operator*=(float s)
        {
            x *s;
            y *s;

            return *this;
        }

        Vec2D &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;

            return *this;
        }
    };

    inline Vec2D operator*(const Vec2D &vec, float s)
    {
        return (Vec2D(vec.x * s, vec.y * s));
    }

    inline Vec2D operator/(const Vec2D &vec, float s)
    {
        s = 1.0f / s;
        return (Vec2D(vec.x * s, vec.y * s));
    }

    inline Vec2D operator-(const Vec2D &vec)
    {
        return (Vec2D(-vec.x, -vec.y));
    }

    inline float Magnitude(const Vec2D &vec)
    {
        return (sqrt(vec.x * vec.x + vec.y * vec.y));
    }

    inline Vec2D Normalize(const Vec2D &vec)
    {
        return (vec / Magnitude(vec));
    }
}// namespace Agate
