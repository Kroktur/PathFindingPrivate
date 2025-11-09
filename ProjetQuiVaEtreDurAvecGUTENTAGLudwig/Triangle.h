#pragma once
#include "Vector2.h"
#include "Vector3.h"

struct Triangle
{
    Point3F A, B, C;

    Vector2F AB, BC, CA;

    Triangle(Point3F a, Point3F b, Point3F c) : A(a), B(b), C(c),
    AB(B.x - A.x, B.z - A.z),
    BC(C.x - B.x, C.z - B.z),
    CA(A.x - C.x, A.z - C.z)
    {
    }

    bool testPointTriangle(const Point3F& P) const
    {
        Vector2F AP(P.x - A.x, P.y - A.y);
        Vector2F BP(P.x - A.x, P.y - A.y);
        Vector2F CP(P.x - A.x, P.y - A.y);

        float test1 = AB.Cross(AP);
        float test2 = BC.Cross(BP);
        float test3 = CA.Cross(CP);

        return ((test1 >= 0 && test2 >= 0 && test3 >= 0) ||
            (test1 <= 0 && test2 <= 0 && test3 <= 0));
    }
};

struct Limits
{
    float x_min, x_max;
    float y_min , y_max;

    static Limits limit(const Triangle& tri)
    {
        Limits l;
        l.x_min = std::floor(std::min(std::min(tri.A.x, tri.B.x), tri.C.x));
        l.x_max = std::ceil(std::max(std::max(tri.A.x, tri.B.x), tri.C.x));

        l.y_min = std::floor(std::min(std::min(tri.A.y, tri.B.y), tri.C.y));
        l.y_max = std::ceil(std::max(std::max(tri.A.y, tri.B.y), tri.C.y));

        return l;
    }
};

