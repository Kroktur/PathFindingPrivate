#pragma once
#include "Vertex.h"
#include <unordered_map>
struct Triangle2d
{
	Vector3F GetNormal() const ;
	std::array<Vertex, 3> points;
    Vector3F GetCircumcenter() const {
        const auto& A = points[0].position;
        const auto& B = points[1].position;
        const auto& C = points[2].position;

        float x1 = A.x, y1 = A.y;
        float x2 = B.x, y2 = B.y;
        float x3 = C.x, y3 = C.y;
        float D = 2.0f * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        float Ux = ((x1 * x1 + y1 * y1) * (y2 - y3) +
            (x2 * x2 + y2 * y2) * (y3 - y1) +
            (x3 * x3 + y3 * y3) * (y1 - y2)) / D;

        float Uy = ((x1 * x1 + y1 * y1) * (x3 - x2) +
            (x2 * x2 + y2 * y2) * (x1 - x3) +
            (x3 * x3 + y3 * y3) * (x2 - x1)) / D;

        return Vector3F(Ux, Uy, 0.0f);
    }
};

//move to c++
inline Vector3F Triangle2d::GetNormal() const 
{
	auto Ab = Vector3F(points[0].position, points[1].position);
	auto Ac = Vector3F(points[0].position, points[2].position);
	return Ab.Cross(Ac);
}