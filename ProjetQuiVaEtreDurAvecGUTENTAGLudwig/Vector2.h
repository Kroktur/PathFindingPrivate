#pragma once
#include "VectorND.h"
template<typename type>
class Vector2 : public VectorND<type, 2>
{
public:
	type& x;
	type& y;
	using value_type = type;
	using class_type = Vector2<type>;
	Vector2();
	Vector2(const value_type& x_, const value_type& y_);
	Vector2(const class_type& other);
	Vector2(class_type&& other) noexcept;
	Vector2(const class_type& lhs, const class_type& rhs);
	class_type& operator=(const class_type&);
	class_type& operator=(class_type&&) noexcept;
	class_type& operator=(const VectorND<type, 2>& other);
	class_type& operator=(VectorND<type, 2>&& other) noexcept;
	class_type NormalVector() const;
	float Cross(const class_type& other) const;
};

template<typename type>
using  Point2 = Vector2<type>;
using  Point2F = Point2<float>;
using  Point2I = Point2<int>;
using  Point2UI = Point2<unsigned int>;


using  Vector2F = Vector2<float>;
using  Vector2I = Vector2<int>;
using  Vector2UI = Vector2<unsigned int>;

template <typename type>
Vector2<type>::Vector2() : VectorND<type, 2>(), x(this->m_data[0]), y(this->m_data[1])
{
}

template <typename type>
Vector2<type>::Vector2(const value_type& x_, const value_type& y_) : VectorND<type, 2>(x_, y_), x(this->m_data[0]), y(this->m_data[1])
{
}

template <typename type>
Vector2<type>::Vector2(const class_type& other) : VectorND<type, 2>(other), x(this->m_data[0]), y(this->m_data[1])
{
}

template <typename type>
Vector2<type>::Vector2(class_type&& other) noexcept : VectorND<type, 2>(std::move(other)), x(this->m_data[0]), y(this->m_data[1])
{
}

template <typename type>
Vector2<type>::Vector2(const class_type& lhs, const class_type& rhs) : VectorND<type,2>(lhs,rhs),x(this->m_data[0]),y(this->m_data[1])
{

}

template <typename type>
typename Vector2<type>::class_type& Vector2<type>::operator=(const class_type& other)
{
	VectorND<type, 2>::operator=(other);
	return *this;
}

template <typename type>
typename Vector2<type>::class_type& Vector2<type>::operator=(class_type&& other) noexcept
{

	VectorND<type, 2>::operator=(std::move(other));
	return *this;
}


template <typename type>
typename Vector2<type>::class_type& Vector2<type>::operator=(const VectorND<type, 2>& other)
{
	VectorND<type, 2>::operator=(other);
	return *this;
}

template <typename type>
typename Vector2<type>::class_type& Vector2<type>::operator=(VectorND<type, 2>&& other) noexcept
{
	VectorND<type, 2>::operator=(std::move(other));
	return *this;
}

template <typename type>
typename Vector2<type>::class_type Vector2<type>::NormalVector() const
{
	return class_type(-y, x);
}

template <typename type>
float Vector2<type>::Cross(const class_type& other) const
{
	return x * other.y - y * other.x;
}

