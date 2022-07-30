#pragma once
#include "Execptions.h"
#include <cmath>
namespace Agate
{
    struct API Vec2D {
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
            x *= s;
            y *= s;

            return *this;
        }

        Vec2D &operator/=(float s)
        {
            s = 1.0f / s;
            x *= s;
            y *= s;

            return *this;
        }

        Vec2D &operator+=(Vec2D &vec)
        {
            x += vec.x;
            y += vec.y;

            return *this;
        }

        Vec2D &operator-=(Vec2D &vec)
        {
            x -= vec.x;
            y -= vec.y;

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

    inline Vec2D operator+(Vec2D &vec1, Vec2D &vec2)
    {
        return (Vec2D(vec1.x + vec2.x, vec1.y + vec2.y));
    }

    inline Vec2D operator-(Vec2D &vec1, Vec2D &vec2)
    {
        return (Vec2D(vec1.x - vec2.x, vec1.y - vec2.y));
    }

    inline Vec2D operator+(const Vec2D &vec1, const Vec2D &vec2)
    {
        return (Vec2D(vec1.x + vec2.x, vec1.y + vec2.y));
    }

    inline Vec2D operator-(const Vec2D &vec1, const Vec2D &vec2)
    {
        return (Vec2D(vec1.x - vec2.x, vec1.y - vec2.y));
    }

    inline float Dot(const Vec2D &a, Vec2D &b)
    {
        return (a.x * b.x + a.y * b.y);
    }
}// namespace Agate
