#pragma once
#include "VectorND.h"

template<typename type>
class Vector3 : public VectorND<type, 3>
{
public:
	using value_type = type;
	using class_type = Vector3<type>;
	type& x;
	type& y;
	type& z;
	Vector3() = default;
	Vector3(const value_type& x_, const value_type& y_, const value_type& z_);
	Vector3(const class_type& other);
	Vector3(const class_type& lhs, const class_type& rhs);
	Vector3(class_type&& other) noexcept;
	class_type& operator=(const class_type&) = default;
	class_type& operator=(class_type&&) = default;
	class_type& operator=(const VectorND<type, 3>& other);
	class_type& operator=(VectorND<type, 3>&& other);
	class_type Cross(const class_type&) const;
};

template<typename type>
using  Point3 = Vector3<type>;
using  Point3F = Point3<float>;
using  Point3I = Point3<int>;
using  Point3UI = Point3<unsigned int>;


using  Vector3F = Vector3<float>;
using  Vector3I = Vector3<int>;
using  Vector3UI = Vector3<unsigned int>;

template <typename type>
Vector3<type>::Vector3(const value_type& x_, const value_type& y_, const value_type& z_) : VectorND<type, 3>(x_, y_, z_), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2])
{
}

template <typename type>
Vector3<type>::Vector3(const class_type& other) : VectorND<type, 3>(other), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2])
{
}

template <typename type>
Vector3<type>::Vector3(const class_type& lhs, const class_type& rhs) : VectorND<type, 3>(lhs,rhs), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2])
{

}

template <typename type>
Vector3<type>::Vector3(class_type&& other) noexcept : VectorND<type, 2>(std::move(other)), x(this->m_data[0]), y(this->m_data[1]), z(this->m_data[2])
{
}

template <typename type>
typename Vector3<type>::class_type& Vector3<type>::operator=(const VectorND<type, 3>& other)
{
	VectorND<type, 2>::operator=(other);
	return *this;
}

template <typename type>
typename Vector3<type>::class_type& Vector3<type>::operator=(VectorND<type, 3>&& other)
{

	VectorND<type, 2>::operator=(std::move(other));
	return *this;
}

template <typename type>
typename Vector3<type>::class_type Vector3<type>::Cross(const class_type& other) const
{
	float resultX = y * other.z - z * other.y;
	float resultY = z * other.x - x * other.z;
	float resultZ = x * other.y - y * other.x;
	return class_type{ resultX, resultY, resultZ };
}
