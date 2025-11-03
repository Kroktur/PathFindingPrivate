#pragma once
#include <array>
#include <vector>
#include <iostream>
template<size_t height = 1, size_t width = height>
struct Dimention2d
{
	static_assert(height > 0 && width > 0, "must be at least a 1 by 1 grid");
	static constexpr size_t size_v = height * width;
	static constexpr size_t height_v = height;
	static constexpr size_t width_v = width;
	static size_t GetIndex(size_t row, size_t col)
	{
		return row * width + col;
	}
	static bool IsInRange(size_t row, size_t col)
	{
		if (row < 0 || row >= height)
			return false;
		if (col < 0 || col >= width)
			return false;
		return true;
	}
};

template<typename tabType, size_t height = 1, size_t width = height>
struct Grid2d
{
	using dimention_type = Dimention2d<height, width>;
	Grid2d() = default;
	~Grid2d() = default;
	Grid2d(const Grid2d&) = default;
	Grid2d(Grid2d&&) = default;
	Grid2d(std::array<tabType, dimention_type::size_v> tab) : m_data(tab)
	{
	}
	Grid2d(const  tabType tab[dimention_type::size_v]) : m_data()
	{
		for (size_t i = 0; i < dimention_type::size_v; ++i)
		{
			m_data[i] = tab[i];
		}
	}

	Grid2d& operator=(const Grid2d&) = default;
	Grid2d& operator=(Grid2d&&) = default;
	Grid2d& operator=(std::array<tabType, dimention_type::size_v> tab)
	{
		m_data = tab;
		return *this;
	}
	Grid2d& operator=(const  tabType tab[dimention_type::size_v])
	{
		for (size_t i = 0; i < dimention_type::size_v; ++i)
		{
			m_data[i] = tab[i];
		}
		return *this;
	}

	tabType& operator[](size_t index)
	{
		return m_data[index];
	}
	const tabType& operator[](size_t index) const
	{
		return m_data[index];
	}
	tabType& At(size_t index)
	{
		return m_data.at(index);
	}
	const tabType& At(size_t index) const
	{
		return m_data.at(index);
	}

	void DrawGrid() const
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
private:
	std::array<tabType, dimention_type::size_v> m_data;
};

static constexpr bool grille[] = {
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
	0, 0, 0, 0, 0, 0, 1, 1, 1, 0
};

template<typename tabType, size_t height, size_t width = height>
static void FloodFillFn(Grid2d<tabType, height, width>& tab, size_t index, const tabType& compareValue)
{
	if (tab[index] != compareValue)
		return;
	tab[index] = 0;
	size_t row = index / width;
	size_t col = index - row * width;
	if (Dimention2d<height, width>::IsInRange(row - 1, col))
		FloodFillFn(tab, Dimention2d<height, width>::GetIndex(row - 1, col), compareValue);
	if (Dimention2d<height, width>::IsInRange(row + 1, col))
		FloodFillFn(tab, Dimention2d<height, width>::GetIndex(row + 1, col), compareValue);
	if (Dimention2d<height, width>::IsInRange(row, col - 1))
		FloodFillFn(tab, Dimention2d<height, width>::GetIndex(row, col - 1), compareValue);
	if (Dimention2d<height, width>::IsInRange(row, col + 1))
		FloodFillFn(tab, Dimention2d<height, width>::GetIndex(row, col + 1), compareValue);
}


template<typename tabType, size_t height, size_t width = height>
static void FloodFillIterative(Grid2d<tabType, height, width>& tab, size_t index, const tabType& compareValue)
{
	std::vector<size_t> toVisit;
	toVisit.push_back(index);

	size_t currentIndex = 0;
	while (!toVisit.empty())
	{
		currentIndex = toVisit.front();

		toVisit.erase(toVisit.begin());

		if (tab[currentIndex] != compareValue)
			continue;
		tab[currentIndex] = 0;
		size_t row = currentIndex / width;
		size_t col = currentIndex - row * width;
		if (row != 0)
			toVisit.push_back(Dimention2d<height, width>::GetIndex(row - 1, col));
		if (row != height - 1)
			toVisit.push_back(Dimention2d<height, width>::GetIndex(row + 1, col));
		if (col != 0)
			toVisit.push_back(Dimention2d<height, width>::GetIndex(row, col - 1));
		if (col != width - 1)
			toVisit.push_back(Dimention2d<height, width>::GetIndex(row, col + 1));
	}
}

template<typename type>
struct FloodFill
{

};
