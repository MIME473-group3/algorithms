/*
 * utils.h
 *
 *  Created on: Jul 20, 2014
 *      Author: Adam Kosiorek
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <chrono>
#include <iostream>
using namespace std;

template<int N = 1, class Fun, class... Args>
void timeExec(string name, Fun fun, Args... args) {

	auto start = chrono::steady_clock::now();

	for(int i = 0; i < N; ++i) {
		fun(args...);
	}

	auto end = chrono::steady_clock::now();

	auto diff = end - start;
	cout << name << ": "<< chrono::duration<double, milli>(diff).count() << " ms. Result = " << fun(args...) << endl;
}

#endif /* UTILS_H_ */
