#pragma once

#include <vector>
#include <cassert>

template <typename T>
class GenericGrid
{
public:
	GenericGrid(std::size_t sizeX, std::size_t sizeY)
	{
		m_sizeX = sizeX;
		m_sizeY = sizeY;
		grid.resize(sizeX * sizeY);
	}
	
	std::size_t getSizeX() const { return m_sizeX; }
	std::size_t getSizeY() const { return m_sizeY; }

	T& at(std::size_t x, std::size_t y) { return grid[getIdx(x,y)]; }
	const T& at(std::size_t x, std::size_t y) const { return grid[getIdx(x,y)]; }
private:
	std::size_t getIdx(std::size_t x, std::size_t y) const
	{
		assert(x < m_sizeX && y < m_sizeY);
		return y * m_sizeX + x;	
	}
	
	std::size_t m_sizeX;
	std::size_t m_sizeY;
	std::vector<T> grid;
};
