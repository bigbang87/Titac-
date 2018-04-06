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

	T& at(std::size_t x, std::size_t y) { return grid[getIdx(x, y)]; }
	const T& at(std::size_t x, std::size_t y) const { return grid[getIdx(x, y)]; }

private:
	std::size_t getIdx(std::size_t x, std::size_t y) const
	{
		assert(x < m_sizeX && y < m_sizeY);
		return (m_sizeX * y) + x;
	}

private:
	std::size_t m_sizeX;
	std::size_t m_sizeY;
	std::vector<T> grid;

	template <typename T>
	class Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		Iterator(T* element) : m_element(element) {};
		T& operator*() const { return m_element; }
		T* operator->() const { return m_element + m_index; }

		bool operator==(const Iterator& rhs) const { return m_element == rhs.m_element && m_index == rhs.m_index; }
		bool operator!=(const Iterator& rhs) const { return m_element != rhs.m_element || m_index != rhs.m_index; }
		bool operator<(const Iterator& rhs) const { return m_index < rhs.m_index; }
		bool operator<=(const Iterator& rhs) const { return m_index <= rhs.m_index; }
		bool operator>(const Iterator& rhs) const { return m_index > rhs.m_index; }
		bool operator>=(const Iterator& rhs) const { return m_index >= rhs.m_index; }

		Iterator operator+(std::size_t index) const { return Iterator(m_element, m_index + index); }
		Iterator operator-(std::size_t index) const { return Iterator(m_element, m_index - index); }
		Iterator& operator+=(std::size_t index) { m_index += index; return *this; }
		Iterator& operator-=(std::size_t index) { m_index -= index; return *this; }
		Iterator& operator++() { ++m_index; return *this; }
		Iterator operator++(int) { Iterator ret(m_element, m_index); ++m_index; return ret; }
		Iterator& operator--() { --m_index; return *this; }
		Iterator operator--(int) { Iterator ret(m_element, m_index); --m_index; return ret; }

	private:
		std::size_t m_index = 0;
		T* m_element = nullptr;
	};

	template <typename T>
	class ConstIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		ConstIterator(T* element) : m_element(element) {};
		const T& operator*() const { return m_element; }
		const T* operator->() const { return m_element + m_index; }

		bool operator==(const ConstIterator& rhs) const { return m_element == rhs.m_element && m_index == rhs.m_index; }
		bool operator!=(const ConstIterator& rhs) const { return m_element != rhs.m_element || m_index != rhs.m_index; }
		bool operator<(const ConstIterator& rhs) const { return m_index < rhs.m_index; }
		bool operator<=(const ConstIterator& rhs) const { return m_index <= rhs.m_index; }
		bool operator>(const ConstIterator& rhs) const { return m_index > rhs.m_index; }
		bool operator>=(const ConstIterator& rhs) const { return m_index >= rhs.m_index; }

		ConstIterator operator+(std::size_t index) const { return Iterator(m_element, m_index + index); }
		ConstIterator operator-(std::size_t index) const { return Iterator(m_element, m_index - index); }
		ConstIterator& operator+=(std::size_t index) { m_index += index; return *this; }
		ConstIterator& operator-=(std::size_t index) { m_index -= index; return *this; }
		ConstIterator& operator++() { ++m_index; return *this; }
		ConstIterator operator++(int) { Iterator ret(m_element, m_index); ++m_index; return ret; }
		ConstIterator& operator--() { --m_index; return *this; }
		ConstIterator operator--(int) { Iterator ret(m_element, m_index); --m_index; return ret; }

	private:
		std::size_t m_index = 0;
		T* m_element = nullptr;
	};
};