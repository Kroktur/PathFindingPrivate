#pragma once
#include "Vector3.h"
#include "Vector2.h"
template<typename type,size_t size>
struct AABB;

template<typename type>
struct AABB<type,3>
{
	using value_type = type;
	using class_type = AABB<type, 3>;
	using vector_type = Vector3<type>;
	AABB();
	AABB(const vector_type& Amin_, const vector_type& Amax_);
	AABB(const class_type& other);
	AABB(class_type&& other) noexcept;

	class_type& operator=(const class_type& other);
	class_type& operator=(class_type&& other) noexcept;

	bool operator==(const class_type& other) const;
	bool operator!=(const class_type& other) const;

	bool operator>(const class_type& other) const;
	bool operator>=(const class_type& other) const;
	bool operator<(const class_type& other) const;
	bool operator<=(const class_type& other) const;

	vector_type Center() const;
	vector_type Size() const;
	vector_type HalfSize() const;
	class_type& Merge(const class_type& other);
	class_type& Expand(const vector_type& vec);
	type BoundingRadius() const;
	type Volume() const;

	bool Contains(const vector_type& vec) const;
	bool Intersects(const vector_type& vec) const;
	bool Contains(const class_type& other) const;
	bool Intersects(const class_type& other) const;

	vector_type Amin, Amax;
};

template<typename type>
using AABB3D = AABB<type, 3>;
using AABB3DF = AABB3D<float>;
using AABB3DI = AABB3D<int>;

template <typename type>
AABB<type, 3>::AABB(): Amin(),Amax()
{
		
}

template <typename type>
AABB<type, 3>::AABB(const vector_type& Amin_, const vector_type& Amax_):Amin(Amin_),Amax(Amax_)
{
		
}

template <typename type>
AABB<type, 3>::AABB(const class_type& other): Amin(other.Amin),Amax(other.Amax)
{
		
}

template <typename type>
AABB<type, 3>::AABB(class_type&& other) noexcept: Amin(std::move(other.Amin)),Amax(std::move(other.Amax))
{
		
}

template <typename type>
bool AABB<type, 3>::Contains(const vector_type& vec) const
{
	if (Amax.x < vec.x || Amin.x > vec.x ||
		Amax.y <vec.y || Amin.y > vec.y ||
		Amax.z < vec.z || Amin.z > vec.z)
		return false;
	return true;
}

template <typename type>
bool AABB<type, 3>::Intersects(const vector_type& vec) const
{
	if (Amax.x <= vec.x || Amin.x >= vec.x ||
		Amax.y <= vec.y || Amin.y >= vec.y ||
		Amax.z <= vec.z || Amin.z >= vec.z)
		return false;
	return true;
}

template <typename type>
bool AABB<type, 3>::Contains(const class_type& other) const
{
	if (Amax.x < other.Amin.x || Amin.x > other.Amax.x ||
		Amax.y < other.Amin.y || Amin.y > other.Amax.y ||
		Amax.z < other.Amin.z || Amin.z > other.Amax.z)
		return false;
	return true;
}

template <typename type>
bool AABB<type, 3>::Intersects(const class_type& other) const
{
	if (Amax.x <= other.Amin.x || Amin.x >= other.Amax.x ||
		Amax.y <= other.Amin.y || Amin.y >= other.Amax.y ||
		Amax.z <= other.Amin.z || Amin.z >= other.Amax.z)
		return false;
	return true;
}

template <typename type>
typename AABB<type, 3>::class_type& AABB<type, 3>::operator=(const class_type& other)
{
	Amin = other.Amin;
	Amax = other.Amax;
	return *this;
}

template <typename type>
typename AABB<type, 3>::class_type& AABB<type, 3>::operator=(class_type&& other) noexcept
{
	Amin = std::move(other.Amin);
	Amax = std::move(other.Amax);
	return *this;
}

template <typename type>
bool AABB<type, 3>::operator==(const class_type& other) const
{
	return  Amin == other.Amin && Amax == other.Amax;
}

template <typename type>
bool AABB<type, 3>::operator!=(const class_type& other) const
{
	return Amin != other.Amin || Amax != other.Amax;
}

template <typename type>
typename AABB<type, 3>::vector_type AABB<type, 3>::Center() const
{
	return  Amin + (Amax - Amin) / 2;
}

template <typename type>
typename AABB<type, 3>::class_type& AABB<type, 3>::Merge(const class_type& other)
{
	if (*this == other)
		return *this;
	Amin.x = std::min(Amin.x, other.Amin.x);
	Amin.y = std::min(Amin.y, other.Amin.y);
	Amin.z = std::min(Amin.z, other.Amin.z);
	Amax.x = std::max(Amax.x, other.Amax.x);
	Amax.y = std::max(Amax.y, other.Amax.y);
	Amax.z = std::max(Amax.z, other.Amax.z);
	return *this;
}

template <typename type>
typename AABB<type, 3>::class_type& AABB<type, 3>::Expand(const vector_type& vec)
{
	if (Contains(vec))
		return *this;
	Amin.x = std::min(Amin.x, vec.x);
	Amin.y = std::min(Amin.y, vec.y);
	Amin.z = std::min(Amin.z, vec.z);
	Amax.x = std::max(Amax.x, vec.x);
	Amax.y = std::max(Amax.y, vec.y);
	Amax.z = std::max(Amax.z, vec.z);
	return *this;
}

template <typename type>
typename AABB<type, 3>::vector_type AABB<type, 3>::Size() const
{
	return Amax - Amin;
}

template <typename type>
typename AABB<type, 3>::vector_type AABB<type, 3>::HalfSize() const
{
	return Size() / 2;
}

template <typename type>
type AABB<type, 3>::BoundingRadius() const
{
	return HalfSize().Length();
}

template <typename type>
type AABB<type, 3>::Volume() const
{
	auto size = Size();
	return size.x * size.y * size.z;
}

template <typename type>
bool AABB<type, 3>::operator>(const class_type& other) const
{
	return Volume() > other.Volume();
}

template <typename type>
bool AABB<type, 3>::operator>=(const class_type& other) const
{
	return Volume() >= other.Volume();
}

template <typename type>
bool AABB<type, 3>::operator<(const class_type& other) const
{
	return Volume() < other.Volume();
}

template <typename type>
bool AABB<type, 3>::operator<=(const class_type& other) const
{
	return Volume() <= other.Volume();
}

template<typename type>
struct AABB<type, 2>
{
	using value_type = type;
	using class_type = AABB<type, 2>;
	using vector_type = Vector2<type>;
	AABB();
	AABB(const vector_type& Amin_, const vector_type& Amax_);
	AABB(const class_type& other);
	AABB(class_type&& other) noexcept;

	class_type& operator=(const class_type& other);
	class_type& operator=(class_type&& other) noexcept;

	bool operator==(const class_type& other) const;
	bool operator!=(const class_type& other) const;

	bool operator>(const class_type& other) const;
	bool operator>=(const class_type& other) const;
	bool operator<(const class_type& other) const;
	bool operator<=(const class_type& other) const;

	vector_type Center() const;
	vector_type Size() const;
	vector_type HalfSize() const;
	class_type& Merge(const class_type& other);
	class_type& Expand(const vector_type& vec);
	type BoundingRadius() const;
	type Volume() const;

	bool Contains(const vector_type& vec) const;
	bool Intersects(const vector_type& vec) const;
	bool Contains(const class_type& other) const;
	bool Intersects(const class_type& other) const;

	vector_type Amin, Amax;
};

template<typename type>
using AABB2D = AABB<type, 2>;
using AABB2DF = AABB2D<float>;
using AABB2DI = AABB2D<int>;

template <typename type>
AABB<type, 2>::AABB(): Amin(), Amax()
{

}

template <typename type>
AABB<type, 2>::AABB(const vector_type& Amin_, const vector_type& Amax_):Amin(Amin_), Amax(Amax_)
{

}

template <typename type>
AABB<type, 2>::AABB(const class_type& other): Amin(other.Amin), Amax(other.Amax)
{

}

template <typename type>
AABB<type, 2>::AABB(class_type&& other) noexcept: Amin(std::move(other.Amin)), Amax(std::move(other.Amax))
{

}

template <typename type>
bool AABB<type, 2>::Contains(const vector_type& vec) const
{
	if (Amax.x < vec.x || Amin.x > vec.x ||
		Amax.y <vec.y || Amin.y > vec.y)
		return false;
	return true;
}

template <typename type>
bool AABB<type, 2>::Intersects(const vector_type& vec) const
{
	if (Amax.x <= vec.x || Amin.x >= vec.x ||
		Amax.y <= vec.y || Amin.y >= vec.y)
		return false;
	return true;
}

template <typename type>
bool AABB<type, 2>::Contains(const class_type& other) const
{
	if (Amax.x < other.Amin.x || Amin.x > other.Amax.x ||
		Amax.y < other.Amin.y || Amin.y > other.Amax.y)
		return false;
	return true;
}

template <typename type>
bool AABB<type, 2>::Intersects(const class_type& other) const
{
	if (Amax.x <= other.Amin.x || Amin.x >= other.Amax.x ||
		Amax.y <= other.Amin.y || Amin.y >= other.Amax.y)
		return false;
	return true;
}

template <typename type>
typename AABB<type, 2>::class_type& AABB<type, 2>::operator=(const class_type& other)
{
	Amin = other.Amin;
	Amax = other.Amax;
	return *this;
}

template <typename type>
typename AABB<type, 2>::class_type& AABB<type, 2>::operator=(class_type&& other) noexcept
{
	Amin = std::move(other.Amin);
	Amax = std::move(other.Amax);
	return *this;
}

template <typename type>
bool AABB<type, 2>::operator==(const class_type& other) const
{
	return  Amin == other.Amin && Amax == other.Amax;
}

template <typename type>
bool AABB<type, 2>::operator!=(const class_type& other) const
{
	return Amin != other.Amin || Amax != other.Amax;
}

template <typename type>
typename AABB<type, 2>::vector_type AABB<type, 2>::Center() const
{
	return  Amin + (Amax - Amin) / 2;
}

template <typename type>
typename AABB<type, 2>::class_type& AABB<type, 2>::Merge(const class_type& other)
{
	if (*this == other)
		return *this;
	Amin.x = std::min(Amin.x, other.Amin.x);
	Amin.y = std::min(Amin.y, other.Amin.y);
	Amax.x = std::max(Amax.x, other.Amax.x);
	Amax.y = std::max(Amax.y, other.Amax.y);
	return *this;
}

template <typename type>
typename AABB<type, 2>::class_type& AABB<type, 2>::Expand(const vector_type& vec)
{
	if (Contains(vec))
		return *this;
	Amin.x = std::min(Amin.x, vec.x);
	Amin.y = std::min(Amin.y, vec.y);
	Amax.x = std::max(Amax.x, vec.x);
	Amax.y = std::max(Amax.y, vec.y);
	return *this;
}

template <typename type>
typename AABB<type, 2>::vector_type AABB<type, 2>::Size() const
{
	return Amax - Amin;
}

template <typename type>
typename AABB<type, 2>::vector_type AABB<type, 2>::HalfSize() const
{
	return Size() / 2;
}

template <typename type>
type AABB<type, 2>::BoundingRadius() const
{
	return HalfSize().Length();
}

template <typename type>
type AABB<type, 2>::Volume() const
{
	auto size = Size();
	return size.x * size.y;
}

template <typename type>
bool AABB<type, 2>::operator>(const class_type& other) const
{
	return Volume() > other.Volume();
}

template <typename type>
bool AABB<type, 2>::operator>=(const class_type& other) const
{
	return Volume() >= other.Volume();
}

template <typename type>
bool AABB<type, 2>::operator<(const class_type& other) const
{
	return Volume() < other.Volume();
}

template <typename type>
bool AABB<type, 2>::operator<=(const class_type& other) const
{
	return Volume() <= other.Volume();
}
