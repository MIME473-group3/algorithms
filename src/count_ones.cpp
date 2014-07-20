//============================================================================
// Name        : CountOnes.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

unsigned char countOnes8(ushort num) {

	unsigned char ones = num & 1;
	for(int i = 1; i < 8; ++i)
		ones += (num >> i) & 1;
	return ones;
}

unsigned char countOnes16(ushort num) {

	unsigned char ones = num & 1;
	for(int i = 1; i < 16; ++i)
		ones += (num >> i) & 1;
	return ones;
}

int main() {
	srand (time(NULL));

	const int SIZE = 10000;
	const ushort max = ~0;
	const ushort smallMask = (unsigned char)~0;
	clock_t init, final;
	long count;

	ushort ints[SIZE];
	for(int i = 0; i < SIZE; ++i)
		ints[i] = rand() % max;


	unsigned char lut[256];
	init = clock();
	for(int j = 0; j < 1000; ++j) {
		for(int i = 0; i < 256; ++i) {
			lut[i] = countOnes8(i);
		}
	}
	final = clock();
	std::cout << "lut computed in " << final - init << std::endl;

	unsigned char biglut[max];
	init = clock();
	for(int j = 0; j < 1000; ++j) {
		for(int i = 0; i < max; ++i) {
			lut[i] = countOnes16(i);
		}
	}
	final = clock();
	std::cout << "biglut computed in " << final - init << std::endl;

	init = clock();
	for(int j = 0; j < 1000; ++j) {
		count = 0;
		for(int i = 0; i < SIZE; ++i) {
			count += lut[(ints[i] >> 8)];
			count += lut[ints[i] & smallMask];
		}
	}
	final = clock();
	std::cout << "Lut: There are " << count << " set bits. Counted in " << final - init << std::endl;

	init = clock();
	for(int j = 0; j < 1000; ++j) {
		count = 0;
		for(int i = 0; i < SIZE; ++i) {
			count += biglut[ints[i]];
		}
	}
	final = clock();
	std::cout << "biglut: There are " << count << " set bits. Counted in " << final - init << std::endl;

	init = clock();
	for(int j = 0; j < 1000; ++j) {
		count = 0;
		for(int i = 0; i < SIZE; ++i) {
			count += countOnes16(ints[i]);
		}
	}
	final = clock();
	std::cout << "Normal: There are " << count << " set bits. Counted in " << final - init << std::endl;

	return 0;
}
