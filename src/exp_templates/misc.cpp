/*
 * template.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: Adam Kosiorek
 */

#include "utils.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;


template<int N>
long factorial() {
	return N * factorial<N - 1>();
}

template<>
long factorial<0>() {
	return 1;
}

template<int F>
int square() {
	return F * F;
}

template<int N, int Low = 1, int Heigh = N>
class Root {
	static const int mean = (Low + Heigh) / 2;
	static const bool down = (mean * mean) >= N;
public:
	static const int val = Root<N, down ? Low : mean + 1, down ? mean : Heigh>::val;
};

template<int N, int Middle>
class Root<N, Middle, Middle> {
public:
	static const int val = Middle;
};

template<class T>
struct DotProduct {
	virtual ~DotProduct() = default;
	virtual T evaluate(T* a, T* b, int N) = 0;
};

template<class T>
struct SimpleDotProduct : public DotProduct<T> {
	virtual T evaluate(T* a, T* b, int N) {
		return (*a) * (*b);
	}
};

template<class T>
struct CompositeDotProduct : public DotProduct<T> {
	virtual T evaluate(T* a, T* b, int N) {
		return SimpleDotProduct<T>().evaluate(a, b, N)
		+ ((N == 1) ? 0 : CompositeDotProduct<T>().evaluate(a + 1, b + 1, N - 1));
	}
};

template<class T>
T dot(T* a, T* b, int N) {
	return N == 1 ? SimpleDotProduct<T>().evaluate(a, b, N)
			: CompositeDotProduct<T>().evaluate(a, b, N);
}

template<int N, class T>
struct CompileDot {
	static T evaluate(T* a, T* b) {
		return (*a) * (*b)
		+ CompileDot<N - 1, T>::evaluate(a + 1, b + 1);
	}
};

template<class T>
struct CompileDot<1, T> {
	static T evaluate(T* a, T* b) {
		return (*a) * (*b);
	}
};

int main(int argc, char** argv) {

	srand(0);
	const int TIMES = 100000;
	const int N = 100;
	double* A = new double[N];
	double* B = new double[N];

	auto random = []() { return rand() % 100; };
	generate(A, A + N, random);
	generate(B, B + N, random);

	cout << "Hello World!" << endl;
	cout << "Factorial of 5 is " << factorial<5>() << endl;
	cout << "Sqr of 5 is " << square<5>() << endl;
	cout << "Ceil of root(10) =  " << Root<10>::val << endl;


	cout << "Dot = " << dot(A, B, N) << endl;

	// Bind, lambda and normal function call
	timeExec<TIMES>("bind", std::bind(dot<double>, A, B, N));


	timeExec<1>("lambda", [&]() { for(int i = 0; i < TIMES; ++i) {
		dot(A, B, N);
	}; return dot(A, B, N); });

	timeExec<TIMES>("runtime dot", dot<double>, A, B, N);

	timeExec<TIMES>("compile time dot", CompileDot<N, double>::evaluate, A, B);


	delete[] A;
	delete[] B;

	return 0;
}
