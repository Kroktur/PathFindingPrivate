#pragma once
#include <array>
#include <cmath>
#include <stdexcept>

template<typename type, size_t size>
class VectorND
{
public:
	using value_type = type;
	using class_type = VectorND<value_type, size>;
	static constexpr size_t vector_size_v = size;
	template<typename ...Arg> requires (sizeof...(Arg) <= size) && (... && (is_floating_type_v<Arg> || is_integral_type_v<Arg>))
	 VectorND(const Arg&... args);
	VectorND() = default;
	VectorND(const class_type& lhs, const class_type& rhs);
	VectorND(const class_type&) = default;
	VectorND(class_type&&)noexcept = default;
	~VectorND() = default;
	class_type& operator=(const class_type&) = default;
	class_type& operator=(class_type&&) noexcept = default;
	size_t Size() const;
	bool IsZero() const;
	bool operator==(const class_type& other) const;
	bool operator!=(const class_type& other) const;
	class_type operator +(const class_type& other) const;
	class_type operator -(const class_type& other) const;
	class_type& operator +=(const class_type& other);
	class_type& operator -=(const class_type& other);
	class_type operator *(const type& factor) const;
	class_type operator /(const type& divider) const;
	class_type& operator *=(const type& factor);
	class_type& operator /=(const type& divider);

	type& operator[](const size_t& i);
	const type& operator[](const size_t& i) const;
	type& at(const size_t& index);
	const type& at(const size_t& index) const;


	type Length() const;
	type SquareLength() const;
	class_type normalize() const;
	class_type& selfNormalize();
	class_type dot(const class_type& other) const;
protected:
	std::array<type, size> m_data;
};

template<size_t size>
using  VectorF = VectorND<float, size>;
template< size_t size>
using  VectorI = VectorND<int, size>;
template<size_t size>
using  VectorUI = VectorND<unsigned int, size>;

template<typename type, size_t size>
using  Point = VectorND<type, size>;
template< size_t size>
using  PointF = Point<float, size>;
template<size_t size>
using  PointI = Point<int, size>;
template< size_t size>
using  PointUI = Point<unsigned int, size>;



template <typename type, size_t size>
template <typename ... Arg> requires (sizeof...(Arg) <= size) && (... && (is_floating_type_v<Arg> || is_integral_type_v<Arg>))
VectorND<type, size>::VectorND(const Arg&... args) : m_data(std::array<type, size>{static_cast<type>(args)...})
{
}

template <typename type, size_t size>
VectorND<type, size>::VectorND(const class_type& lhs, const class_type& rhs) : m_data(std::array<type, size>{})
{
	for (int i = 0; i < m_data.size(); ++i)
	{
		m_data[i] = rhs[i] - lhs[i];
	}
}

template <typename type, size_t size>
size_t VectorND<type, size>::Size() const
{
	return size;
}

template <typename type, size_t size>
bool VectorND<type, size>::IsZero() const
{
	for (auto i = 0; i < size; ++i)
	{
		if (m_data[i] != 0)
			return false;
	}
	return true;
}

template <typename type, size_t size>
bool VectorND<type, size>::operator==(const class_type& other) const
{
	return  m_data == other.m_data;
}

template <typename type, size_t size>
bool VectorND<type, size>::operator!=(const class_type& other) const
{
	return  m_data != other.m_data;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type VectorND<type, size>::operator+(const class_type& other) const
{
	class_type result;
	for (auto i = 0; i < size; ++i)
	{
		result[i] = m_data[i] + other[i];
	}
	return result;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type VectorND<type, size>::operator-(const class_type& other) const
{
	class_type result;
	for (auto i = 0; i < size; ++i)
	{
		result[i] = m_data[i] - other[i];
	}
	return result;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type& VectorND<type, size>::operator+=(const class_type& other)
{
	for (auto i = 0; i < size; ++i)
	{
		m_data[i] += other[i];
	}
	return *this;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type& VectorND<type, size>::operator-=(const class_type& other)
{
	for (auto i = 0; i < size; ++i)
	{
		m_data[i] -= other[i];
	}
	return *this;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type VectorND<type, size>::operator*(const type& factor) const
{
	class_type result;
	for (auto i = 0; i < size; ++i)
	{
		result[i] = m_data[i] * factor;
	}
	return result;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type VectorND<type, size>::operator/(const type& divider) const
{
	if (divider == 0)
		throw std::out_of_range("impossible to divide by 0");
	class_type result;
	for (auto i = 0; i < size; ++i)
	{
		result[i] = m_data[i] / divider;
	}
	return result;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type& VectorND<type, size>::operator*=(const type& factor)
{
	for (auto i = 0; i < size; ++i)
	{
		m_data[i] *= factor;
	}
	return *this;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type& VectorND<type, size>::operator/=(const type& divider)
{
	if (divider == 0)
		throw std::out_of_range("impossible to divide by 0");
	for (auto i = 0; i < size; ++i)
	{
		m_data[i] /= divider;
	}
	return *this;
}

template <typename type, size_t size>
type VectorND<type, size>::Length() const
{
	return std::sqrt(SquareLength());
}

template <typename type, size_t size>
type VectorND<type, size>::SquareLength() const
{
	value_type result = value_type{};
	for (auto& it : m_data)
		result += (it * it);
	return  result;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type VectorND<type, size>::normalize() const
{
	if (IsZero())
		throw std::out_of_range("impossible to Normalize null vector");
	auto length = Length();
	return (*this) / length;
}

template <typename type, size_t size>
typename VectorND<type, size>::class_type& VectorND<type, size>::selfNormalize()
{
	if (IsZero())
		throw std::out_of_range("impossible to Normalize null vector");
	auto length = Length();
	return (*this) /= length;
}

template <typename type, size_t size>
const type& VectorND<type, size>::operator[](const size_t& i) const
{
	return m_data[i];
}

template <typename type, size_t size>
type& VectorND<type, size>::at(const size_t& index)
{
	if (index >= size)
		throw std::out_of_range("index not in range");
	return m_data.at(index);
}

template <typename type, size_t size>
const type& VectorND<type, size>::at(const size_t& index) const
{
	if (index >= size)
		throw std::out_of_range("index not in range");
	return m_data.at(index);
}

template <typename type, size_t size>
type& VectorND<type, size>::operator[](const size_t& i)
{
	return m_data[i];
}

template <typename type, size_t size>
VectorND<type, size> VectorND<type, size>::dot(const class_type& other) const
{
	class_type result = class_type{};
	for (int i = 0; i < m_data.size(); ++i)
	{
		result[i] = m_data[i] * other[i];
	}
	return result;
}

template<typename type,size_t size>
std::ostream& operator<<(std::ostream& os , const VectorND<type,size>& vec)
{
	for (int i = 0 ; i < size ; ++i)
	{
		os << vec[i] << " ";
	}
	os << "\n";
	return os;
}