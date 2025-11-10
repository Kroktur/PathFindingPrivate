#pragma once
#include <array>
#include <iostream>
#include <deque>
#include <vector>
#include "PrimaryType_Category.h"
#include <memory>

template<size_t height = 1, size_t width = height>
struct Dimension2dStatic
{
	static_assert(height > 0 && width > 0, "must be at least a 1 by 1 grid");
	static constexpr size_t size_v = height * width;
	static constexpr size_t height_v = height;
	static constexpr size_t width_v = width;
	static size_t GetIndex(size_t row, size_t col);
	static bool IsInRange(size_t row, size_t col);
};

template <size_t height, size_t width>
size_t Dimension2dStatic<height, width>::GetIndex(size_t row, size_t col)
{
	return row * width + col;
}

template <size_t height, size_t width>
bool Dimension2dStatic<height, width>::IsInRange(size_t row, size_t col)
{
	if (row < 0 || row >= height)
		return false;
	if (col < 0 || col >= width)
		return false;
	return true;
}

template<typename tabType, size_t height = 1, size_t width = height>
struct Grid2dStatic
{
	using dimention_type = Dimension2dStatic<height, width>;

	Grid2dStatic() = default;
	~Grid2dStatic() = default;
	Grid2dStatic(const Grid2dStatic&) = default;
	Grid2dStatic(Grid2dStatic&&) = default;
	Grid2dStatic(std::array<tabType, dimention_type::size_v> tab);
	Grid2dStatic(const  tabType tab[dimention_type::size_v]);

	Grid2dStatic& operator=(const Grid2dStatic&) = default;
	Grid2dStatic& operator=(Grid2dStatic&&) = default;
	Grid2dStatic& operator=(std::array<tabType, dimention_type::size_v> tab);
	Grid2dStatic& operator=(const  tabType tab[dimention_type::size_v]);

	tabType& operator[](size_t index);
	const tabType& operator[](size_t index) const;
	tabType& At(size_t index);
	const tabType& At(size_t index) const;

	void DrawGrid() const;

private:
	std::array<tabType, dimention_type::size_v> m_data;
};



template <typename tabType, size_t height, size_t width>
Grid2dStatic<tabType, height, width>::Grid2dStatic(const tabType tab[dimention_type::size_v]): m_data()
{
	for (size_t i = 0; i < dimention_type::size_v; ++i)
	{
		m_data[i] = tab[i];
	}
}


template <typename tabType, size_t height, size_t width>
Grid2dStatic<tabType, height, width>& Grid2dStatic<tabType, height, width>::operator=(
	std::array<tabType, Dimension2dStatic<height, width>::size_v> tab)
{
	m_data = tab;
	return *this;
}

template <typename tabType, size_t height, size_t width>
Grid2dStatic<tabType, height, width>& Grid2dStatic<tabType, height, width>::operator=(const tabType tab[dimention_type::size_v])
{
	for (size_t i = 0; i < dimention_type::size_v; ++i)
	{
		m_data[i] = tab[i];
	}
	return *this;
}

template <typename tabType, size_t height, size_t width>
tabType& Grid2dStatic<tabType, height, width>::operator[](size_t index)
{
	return m_data[index];
}

template <typename tabType, size_t height, size_t width>
const tabType& Grid2dStatic<tabType, height, width>::operator[](size_t index) const
{
	return m_data[index];
}

template <typename tabType, size_t height, size_t width>
tabType& Grid2dStatic<tabType, height, width>::At(size_t index)
{
	return m_data.at(index);
}

template <typename tabType, size_t height, size_t width>
const tabType& Grid2dStatic<tabType, height, width>::At(size_t index) const
{
	return m_data.at(index);
}

template <typename tabType, size_t height, size_t width>
void Grid2dStatic<tabType, height, width>::DrawGrid() const
{
	for (int i = 0; i < height; ++i)
	{
		for (auto j = 0; j < width; ++j)
		{
			std::cout << m_data[i * width + j] << " ";
		}
		std::cout << "\n";
	}
}

template <typename tabType, size_t height, size_t width>
Grid2dStatic<tabType, height, width>::Grid2dStatic(std::array<tabType, Dimension2dStatic<height, width>::size_v> tab): m_data(tab)
{
}

template<typename tabType, size_t height, size_t width = height>
struct FloodFillStatic
{
	template<bool (*ModifyFn)(const tabType& value), void (*AffectationFN)(tabType& value)>
	static void Recursive(Grid2dStatic<tabType, height, width>& tab, size_t index)
	{
		if (!ModifyFn(tab[index]))
			return;
		AffectationFN(tab[index]);
		size_t raw = index / width;
		size_t col = index - raw * width;
		if (Dimension2dStatic<height, width>::IsInRange(raw - 1, col))
			Recursive<ModifyFn, AffectationFN>(tab, Dimension2dStatic<height, width>::GetIndex(raw - 1, col));
		if (Dimension2dStatic<height, width>::IsInRange(raw + 1, col))
			Recursive<ModifyFn, AffectationFN>(tab, Dimension2dStatic<height, width>::GetIndex(raw + 1, col));
		if (Dimension2dStatic<height, width>::IsInRange(raw, col - 1))
			Recursive<ModifyFn, AffectationFN>(tab, Dimension2dStatic<height, width>::GetIndex(raw, col - 1));
		if (Dimension2dStatic<height, width>::IsInRange(raw, col + 1))
			Recursive<ModifyFn, AffectationFN>(tab, Dimension2dStatic<height, width>::GetIndex(raw, col + 1));
	}
	template<bool (*ModifyFn)(const tabType& value), void (*AffectationFN)(tabType& value)>
	static void Iterative(Grid2dStatic<tabType, height, width>& tab, size_t index)
	{
		std::deque<size_t> toVisit;
		toVisit.push_back(index);

		size_t currentIndex = 0;
		while (!toVisit.empty())
		{
			currentIndex = toVisit.front();

			toVisit.pop_front();

			if (!ModifyFn(tab[currentIndex]))
				continue;
			AffectationFN(tab[currentIndex]);
			size_t raw = currentIndex / width;
			size_t col = currentIndex - raw * width;
			if (Dimension2dStatic<height, width>::IsInRange(raw - 1, col))
				toVisit.push_back(Dimension2dStatic<height, width>::GetIndex(raw - 1, col));
			if (Dimension2dStatic<height, width>::IsInRange(raw + 1, col))
				toVisit.push_back(Dimension2dStatic<height, width>::GetIndex(raw + 1, col));
			if (Dimension2dStatic<height, width>::IsInRange(raw, col - 1))
				toVisit.push_back(Dimension2dStatic<height, width>::GetIndex(raw, col - 1));
			if (Dimension2dStatic<height, width>::IsInRange(raw, col + 1))
				toVisit.push_back(Dimension2dStatic<height, width>::GetIndex(raw, col + 1));
		}
	}
};


struct Dimension2d
{
	Dimension2d(size_t height_,size_t width_);
	Dimension2d(const Dimension2d&) = default;
	Dimension2d(Dimension2d&&) noexcept = default;
	size_t GetIndex(size_t row, size_t col) const;
	bool IsInRange(size_t row, size_t col) const;
	size_t Size() const;
	const size_t height, width;
};



template<typename tabType>
struct Grid2d
{
	Grid2d(const Dimension2d& dim);
	~Grid2d() = default;
	Grid2d(const Grid2d&) = default;
	Grid2d(Grid2d&&) noexcept = default;
	Grid2d(const Dimension2d& dim,std::vector<tabType> tab);
	Grid2d(const Dimension2d& dim,const  tabType tab[],size_t count);

	Grid2d& operator=(const Grid2d&) = default;
	Grid2d& operator=(Grid2d&&) noexcept =default;
	Grid2d& operator=(std::vector<tabType> tab);

	tabType& operator[](size_t index);

	const tabType& operator[](size_t index) const;

	tabType& At(size_t index);

	const tabType& At(size_t index) const;

	void DrawGrid() const;

	Dimension2d GetDim() const;

private:
	Dimension2d m_dim;
	std::vector<tabType> m_data;
};


template <typename tabType>
Grid2d<tabType>::Grid2d(const Dimension2d& dim):m_dim(dim)
{
	m_data.resize(m_dim.Size());
}


template <typename tabType>
Grid2d<tabType>::Grid2d(const Dimension2d& dim, std::vector<tabType> tab): m_dim(dim),m_data()
{
	m_data.resize(m_dim.Size());
	if (tab.size() > m_dim.Size())
		throw std::out_of_range("size must be equal or less");
	std::copy(tab.begin(), tab.end(), m_data.begin());
}

template <typename tabType>
Grid2d<tabType>::Grid2d(const Dimension2d& dim, const tabType tab[], size_t count): m_dim(dim),m_data()
{
	m_data.resize(m_dim.Size());
		
	if (count > m_dim.Size())
		throw std::out_of_range("size must be equal or less");
	std::copy(tab, tab + count, m_data.begin());
}

template <typename tabType>
Grid2d<tabType>& Grid2d<tabType>::operator=(std::vector<tabType> tab)
{
	m_data.clear();
	m_data.resize(m_dim.Size());
	if (tab.size() > m_dim.Size())
		throw std::out_of_range("size must be equal or less");
	std::copy(tab.begin(), tab.end(), m_data.begin());
	return *this;
}

template <typename tabType>
tabType& Grid2d<tabType>::operator[](size_t index)
{
	return m_data[index];
}

template <typename tabType>
const tabType& Grid2d<tabType>::operator[](size_t index) const
{
	return m_data[index];
}

template <typename tabType>
tabType& Grid2d<tabType>::At(size_t index)
{
	return m_data.at(index);
}

template <typename tabType>
const tabType& Grid2d<tabType>::At(size_t index) const
{
	return m_data.at(index);
}

template <typename tabType>
void Grid2d<tabType>::DrawGrid() const
{
	for (size_t i = 0; i < m_dim.height; ++i)
	{
		for (size_t j = 0; j < m_dim.width; ++j)
		{
			std::cout << m_data[i * m_dim.width + j] << " ";
		}
		std::cout << "\n";
	}
}

template <typename tabType>
Dimension2d Grid2d<tabType>::GetDim() const
{
	return m_dim;
}

template<typename tabType>
struct FloodFill
{
	template<bool (*ModifyFn)(const tabType& value), void (*AffectationFN)(tabType& value)>
	static void Recursive(Grid2d<tabType>& tab, size_t index);

	template<bool (*ModifyFn)(const tabType& value), void (*AffectationFN)(tabType& value)>
	static void Iterative(Grid2d<tabType>& tab, size_t index);
};

template <typename tabType>
template <bool(* ModifyFn)(const tabType& value), void(* AffectationFN)(tabType& value)>
void FloodFill<tabType>::Recursive(Grid2d<tabType>& tab, size_t index)
{
	if (!ModifyFn(tab[index]))
		return;
	AffectationFN(tab[index]);
	size_t raw = index / tab.GetDim().width;
	size_t col = index - raw * tab.GetDim().width;
	if (tab.GetDim().IsInRange(raw - 1, col))
		Recursive<ModifyFn, AffectationFN>(tab, tab.GetDim().GetIndex(raw - 1, col));
	if (tab.GetDim().IsInRange(raw + 1, col))
		Recursive<ModifyFn, AffectationFN>(tab, tab.GetDim().GetIndex(raw + 1, col));
	if (tab.GetDim().IsInRange(raw, col - 1))
		Recursive<ModifyFn, AffectationFN>(tab, tab.GetDim().GetIndex(raw, col - 1));
	if (tab.GetDim().IsInRange(raw, col + 1))
		Recursive<ModifyFn, AffectationFN>(tab, tab.GetDim().GetIndex(raw, col + 1));
}

template <typename tabType>
template <bool(* ModifyFn)(const tabType& value), void(* AffectationFN)(tabType& value)>
void FloodFill<tabType>::Iterative(Grid2d<tabType>& tab, size_t index)
{
	std::deque<size_t> toVisit;
	toVisit.push_back(index);

	size_t currentIndex = 0;
	while (!toVisit.empty())
	{
		currentIndex = toVisit.front();

		toVisit.pop_front();

		if (!ModifyFn(tab[currentIndex]))
			continue;
		AffectationFN(tab[currentIndex]);
		size_t raw = currentIndex / tab.GetDim().width;
		size_t col = currentIndex - raw * tab.GetDim().width;
		if (tab.GetDim().IsInRange(raw - 1, col))
			toVisit.push_back(tab.GetDim().GetIndex(raw - 1, col));
		if (tab.GetDim().IsInRange(raw + 1, col))
			toVisit.push_back(tab.GetDim().GetIndex(raw + 1, col));
		if (tab.GetDim().IsInRange(raw, col - 1))
			toVisit.push_back(tab.GetDim().GetIndex(raw, col - 1));
		if (tab.GetDim().IsInRange(raw, col + 1))
			toVisit.push_back(tab.GetDim().GetIndex(raw, col + 1));
	}
}
