#pragma once
#include "Vertex.h"
#include <unordered_map>

#include "Matrix.h"

struct Triangle2d
{
	Vector3F GetNormal() const ;
	std::array<Vertex, 3> points;
    Vector3F GetCircumcenter() const {
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
                                 (GetNormal().dot(A) * 2)};

        

        Matrix<float, 3, 1> U = Am.Inverse().MatrixProduct(Bm) * 1.0f/2.0f;
    	return Vector3F( U[0],  U[1],  U[2]);
    }
    bool IsCircumcenter(const Point3F& point) const
    {
        Vector3F n = GetNormal();
        n.selfNormalize();

        Vector3F AP = Vector3F(points[0].position, point);
        float distToPlane = std::abs(n.dot(AP));
        if (distToPlane > Math::EPSILON_FLOAT)
            return false; 

        auto Ap = Vector3F(points[0].position, point);
        auto Bp = Vector3F(points[1].position, point);
        auto Cp = Vector3F(points[2].position, point);
        if (Math::IsSameValue(Ap.Length(), Bp.Length(), Math::EPSILON_FLOAT) && Math::IsSameValue(Ap.Length(), Cp.Length(), Math::EPSILON_FLOAT))
            return true;
        return false;
    }
};

//move to c++   
inline Vector3F Triangle2d::GetNormal() const 
{
	auto Ab = Vector3F(points[0].position, points[1].position);
	auto Ac = Vector3F(points[0].position, points[2].position);
	return Ab.Cross(Ac);
}