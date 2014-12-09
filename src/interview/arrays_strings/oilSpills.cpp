/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <array>
#include <ostream>
#include <queue>

template<class T>
class Array2D {
	T* data;

	class IndexHelper {
		Array2D& array2D;
		int y;
	public:
		IndexHelper(Array2D& array2D, int y) : array2D(array2D), y(y) {};

		T& operator[] (int x) {
			return array2D.at(y, x);
		}

		const T& operator[] (int x) const {
			return (*const_cast<IndexHelper*>(this))[x];
		}
	};

public:
	Array2D(int width, int height)
	: width(width), height(height), data(new T[width * height]) {}

	Array2D(int width, int height, T initValue)
	: Array2D(width, height) {

		for(int i = 0; i < width * height; ++i) {
			data[i] = initValue;
		}
	}

	~Array2D() {
		delete[] data;
	}

	IndexHelper operator[] (int y) {
		return IndexHelper(*this, y);
	}

	const IndexHelper operator[] (int y) const {
		return (*const_cast<Array2D<T>*>(this))[y];
	}

	T& at(int y, int x) {
		return data[y * width + x];
	}

	const T& at(int y, int x) const {
		return const_cast<Array2D<T>*>(this)->at(y, x);
	}

	friend std::ostream& operator<<(std::ostream& out, const Array2D<T>& array) {
		int i = 0;
		for(int y = 0; y < array.width; ++y) {
			for(int x = 0; x < array.height; ++x) {
				out << array.data[i++] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	const int width;
	const int height;
};

bool isSafe(const Array2D<bool>& water, Array2D<bool>& visited, int x, int y) {
	if(x < 0 || x > water.width || y < 0 || y > water.height || water[y][x] || visited[y][x]) {
		return false;
	}
	return true;
}

void visitDFS(const Array2D<bool>& water, Array2D<bool>& visited, int x, int y) {
	if(isSafe(water, visited, x, y)) {
		visited[y][x] = true;
		visitDFS(water, visited, x - 1, y);
		visitDFS(water, visited, x + 1, y);
		visitDFS(water, visited, x, y - 1);
		visitDFS(water, visited, x, y + 1);
	}
}

void visitBFS(const Array2D<bool>& water, Array2D<bool>& visited, int x, int y) {

	struct Point {
		int x, y;
		Point(int x, int y) : x(x), y(y) {}
	};

	std::queue<Point> vertexQueue;
	vertexQueue.emplace(x, y);

	while(!vertexQueue.empty()) {
		auto p = vertexQueue.front();
		vertexQueue.pop();
		if(!isSafe(water, visited, p.x, p.y)) {
			continue;
		}
		visited[p.y][p.x] = true;
		vertexQueue.emplace(p.x + 1, p.y);
		vertexQueue.emplace(p.x - 1, p.y);
		vertexQueue.emplace(p.x, p.y + 1);
		vertexQueue.emplace(p.x, p.y - 1);
	}
}

int numOilSpills(const Array2D<bool>& water) {

	Array2D<bool> visited(water.width, water.height, false);

	int count = 0;
	for(int y = 0; y < water.height; ++y) {
		for(int x = 0; x < water.width; ++x) {
			if(!water[y][x] && !visited[y][x]) {
				++count;
				visitDFS(water, visited, x, y);
			}
		}
	}
	return count;
}

int numOilSpillsBFS(const Array2D<bool>& water) {

	Array2D<bool> visited(water.width, water.height, false);

	int count = 0;
	for(int y = 0; y < water.height; ++y) {
		for(int x = 0; x < water.width; ++x) {
			if(!water[y][x] && !visited[y][x]) {
				++count;
				visitBFS(water, visited, x, y);
			}
		}
	}
	return count;
}

struct OilSpillsTest : public testing::Test {};


TEST_F(OilSpillsTest, DFSTest) {

	Array2D<bool> water(5, 5, 1);
	ASSERT_EQ(numOilSpills(water), 0);
	water[1][1] = 0;
	ASSERT_EQ(numOilSpills(water), 1);
	water[1][3] = 0;
	ASSERT_EQ(numOilSpills(water), 2);
	water[3][1] = 0;
	ASSERT_EQ(numOilSpills(water), 3);
	water[3][3] = 0;
	ASSERT_EQ(numOilSpills(water), 4);
	water[2][2] = 0;
	ASSERT_EQ(numOilSpills(water), 5);

	water[2][1] = 0;
	ASSERT_EQ(numOilSpills(water), 3);

	water[2][3] = 0;
	ASSERT_EQ(numOilSpills(water), 1);
}

TEST_F(OilSpillsTest, BFSTest) {

	Array2D<bool> water(5, 5, 1);
	ASSERT_EQ(numOilSpillsBFS(water), 0);
	water[1][1] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 1);
	water[1][3] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 2);
	water[3][1] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 3);
	water[3][3] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 4);
	water[2][2] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 5);

	water[2][1] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 3);

	water[2][3] = 0;
	ASSERT_EQ(numOilSpillsBFS(water), 1);
}

