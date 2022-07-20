#pragma once

#include "Execptions.h"
#include "Vect3D.h"

namespace Agate
{
    struct API Mat3D {
    private:
        float n[3][3];

    public:
        Mat3D() = default;

        Mat3D(float n00, float n01, float n02,
              float n10, float n11, float n12,
              float n20, float n21, float n22)
        {
            n[0][0] = n00;
            n[1][0] = n01;
            n[2][0] = n02;
            n[0][1] = n10;
            n[1][1] = n11;
            n[2][1] = n12;
            n[0][2] = n20;
            n[1][2] = n21;
            n[2][2] = n22;
        }

        Mat3D(const Vec3D &a, const Vec3D &b, const Vec3D &c)
        {
            n[0][0] = a.x;
            n[1][0] = b.x;
            n[2][0] = c.x;
            n[0][1] = a.y;
            n[1][1] = b.y;
            n[2][1] = c.y;
            n[0][2] = a.z;
            n[1][2] = b.z;
            n[2][2] = c.z;
        }

        float &operator()(int i, int j)
        {
            if (i < 3 && j < 3)
                return (n[j][i]);
            else
                throw OutOfBonds();
        }

        const float &operator()(int i, int j) const
        {
            if (i < 3 && j < 3)
                return (n[j][i]);
            else
                throw OutOfBonds();
        }

        Vec3D &operator[](int j)
        {
            if (j < 3)
                return (*reinterpret_cast<Vec3D *>(n[j]));
            else
                throw OutOfBonds();
        }

        const Vec3D &operator[](int j) const
        {
            if (j < 3)
                return (*reinterpret_cast<const Vec3D *>(n[j]));
            else
                throw OutOfBonds();
        }
    };

    Mat3D operator*(const Mat3D &a, const Mat3D &b)
    {
        return (Mat3D(a(0, 0) * b(0, 0) + a(0, 1) * b(1, 0) + a(0, 2) * b(2, 0),
                      a(0, 0) * b(0, 1) + a(0, 1) * b(1, 1) + a(0, 2) * b(2, 1),
                      a(0, 0) * b(0, 2) + a(0, 1) * b(1, 2) + a(0, 2) * b(2, 2),
                      a(1, 0) * b(0, 0) + a(1, 1) * b(1, 0) + a(1, 2) * b(2, 0),
                      a(1, 0) * b(0, 1) + a(1, 1) * b(1, 1) + a(1, 2) * b(2, 1),
                      a(1, 0) * b(0, 2) + a(1, 1) * b(1, 2) + a(1, 2) * b(2, 2),
                      a(2, 0) * b(0, 0) + a(2, 1) * b(1, 0) + a(2, 2) * b(2, 0),
                      a(2, 0) * b(0, 1) + a(2, 1) * b(1, 1) + a(2, 2) * b(2, 1),
                      a(2, 0) * b(0, 2) + a(2, 1) * b(1, 2) + a(2, 2) * b(2, 2)));
    }

    Vec3D operator*(const Mat3D &M, const Vec3D &v)
    {
        return (Vec3D((M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z),
                      (M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z),
                      (M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z)));
    }
}// namespace Agate
