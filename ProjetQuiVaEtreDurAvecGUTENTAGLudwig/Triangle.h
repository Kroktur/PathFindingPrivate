#pragma once
#include "Vector2.h"
#include "Vector3.h"

struct Triangle2
{
    Point3F A, B, C;

    Vector2F AB, BC, CA;

    Triangle2(Point3F a, Point3F b, Point3F c) : A(a), B(b), C(c),
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

    static Limits limit(const Triangle2& tri)
    {
        Limits l;
        l.x_min = std::floor(std::min(std::min(tri.A.x, tri.B.x), tri.C.x));
        l.x_max = std::ceil(std::max(std::max(tri.A.x, tri.B.x), tri.C.x));

        l.y_min = std::floor(std::min(std::min(tri.A.y, tri.B.y), tri.C.y));
        l.y_max = std::ceil(std::max(std::max(tri.A.y, tri.B.y), tri.C.y));

        return l;
    }
};

#include "Vertex.h"
#include <unordered_map>

#include "Matrix.h"

struct Triangle
{
	Vector3F GetNormal() const ;
	std::array<Vertex, 3> points;
    Vector3F GetCircumcenter() const;
	bool IsCircumcenter(const Point3F& point) const;

    bool testPointTriangle(const Point3F& P) const
    {
        const Vector3F& A = points[0].position;
        const Vector3F& B = points[1].position;
        const Vector3F& C = points[2].position;

        Vector3F AB = B - A;
        Vector3F BC = C - B;
        Vector3F CA = A - C;

        Vector3F AP = P - A;
        Vector3F BP = P - B;
        Vector3F CP = P - C;

        Vector3F N = GetNormal();

        Vector3F cross1 = AB.Cross(AP);
        Vector3F cross2 = BC.Cross(BP);
        Vector3F cross3 = CA.Cross(CP);

        if (cross1.Dot(N) >= 0 && cross2.Dot(N) >= 0 && cross3.Dot(N) >= 0)
            return true;
        if (cross1.Dot(N) <= 0 && cross2.Dot(N) <= 0 && cross3.Dot(N) <= 0)
            return true;

        return false;
    }
};

//move to c++   
inline Vector3F Triangle::GetNormal() const 
{
	auto Ab = Vector3F(points[0].position, points[1].position);
	auto Ac = Vector3F(points[0].position, points[2].position);
	return Ab.Cross(Ac);
}

inline Vector3F Triangle::GetCircumcenter() const
{
	const auto& A = points[0].position;
	const auto& B = points[1].position;
	const auto& C = points[2].position;
	float x1 = A.x,y1 = A.y, z1 = A.z;
	float x2 = B.x,y2 = B.y, z2 = B.z;
	float x3 = C.x,y3 = C.y, z3 = C.z;

	Matrix<float, 3,3> Am{ x2-x1,y2-y1,z2-z1,
		x3-x1,y3-y1,z3-z1,
		GetNormal().x,GetNormal().y,GetNormal().z};
	Matrix<float,3,1> Bm = {Math::Pow(x2,2) +Math::Pow(y2,2)+ Math::Pow(z2,2) - (Math::Pow(x1,2) +Math::Pow(y1,2) +Math::Pow(z1,2) )
		,Math::Pow(x3,2) +Math::Pow(y3,2)+ Math::Pow(z3,2) - (Math::Pow(x1,2) +Math::Pow(y1,2)+ Math::Pow(z1,2)),
		(GetNormal().Dot(A) * 2)};

        

	Matrix<float, 3, 1> U = Am.Inverse().MatrixProduct(Bm) * 1.0f/2.0f;
	return Vector3F( U[0],  U[1],  U[2]);
}

inline bool Triangle::IsCircumcenter(const Point3F& point) const
{
	Vector3F n = GetNormal();
	n.selfNormalize();

	Vector3F AP = Vector3F(points[0].position, point);
	float distToPlane = std::abs(n.Dot(AP));
	if (distToPlane > Math::EPSILON_FLOAT)
		return false; 

	auto Ap = Vector3F(points[0].position, point);
	auto Bp = Vector3F(points[1].position, point);
	auto Cp = Vector3F(points[2].position, point);
	if (Math::IsSameValue(Ap.Length(), Bp.Length(), Math::EPSILON_FLOAT) && Math::IsSameValue(Ap.Length(), Cp.Length(), Math::EPSILON_FLOAT))
		return true;
	return false;
}
