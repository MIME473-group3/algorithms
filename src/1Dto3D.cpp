/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"


const int WIDTH = 4;
const int LENGTH = 5;
const int DEPTH = 6;

int index(int x, int y, int z) {
	return z * LENGTH * WIDTH + y * LENGTH + x;
}

struct Test : public testing::Test {


};


TEST_F(Test, SomeTest) {

	int D3[DEPTH][WIDTH][LENGTH];
	int D1[DEPTH * WIDTH * LENGTH];

	for(int z = 0; z < DEPTH; ++z) {
		for(int y = 0; y < WIDTH; ++y) {
			for(int x = 0; x < LENGTH; ++x) {
				D3[z][y][x] = index(x, y, z);
				D1[index(x, y, z)] = index(x, y, z);
			}
		}
	}

	for(int i = 0; i < DEPTH * WIDTH * LENGTH; ++i) {
		std::cout << *(D1 + i) << " ";
	}
	std::cout << std::endl;


	for(int z = 0; z < DEPTH; ++z) {
		for(int y = 0; y < WIDTH; ++y) {
			for(int x = 0; x < LENGTH; ++x) {
				std::cout << D3[z][y][x] << " ";
			}
		}
	}
	std::cout << std::endl;

}

