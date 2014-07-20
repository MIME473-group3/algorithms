/*
 * compiler.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: Adam Kosiorek
 */

#include "compiler.h"
#include "utils.h"
#include <iostream>
#include <functional>
using namespace std;

int main(int argc, char** argv) {

	cout << "Hello World!" << endl;

	double x;
//	BinaryExpr<Variable, Constant, Product> X2(Variable(x), Constant(2));
//	BinaryExpr<decltype(X2), Constant, Sum> X2plus3(X2, three);
//	BinaryExpr<decltype(X2plus3), Constant, Product> X2plus3o25(X2plus3, Constant(.25));
//	BinaryExpr<decltype(X2plus3o25), Constant, Sum> almost(X2plus3o25, one);
//	UnaryExpr<decltype(almost), Sigmoid> result(almost);

//	auto X2 = Variable(x) * Constant(2.);
//	auto X2plus3 = X2 + Constant(3.);
//	auto X2plus3o25 = X2plus3 * Constant(.25);
//	auto almost = X2plus3o25 + Constant(1.);
//	auto result = sigmoid(almost);

	auto result = sigmoid((2 * Variable(x) + 3) * .25 + 1);

	cout << "sigmoid((2x + 3) * 0.25 + 1) =" << endl;
	x = .25;
	printf("x = %.2f: %.4f\n", x, result.eval());
	x = .5;
	printf("x = %.2f: %.4f\n", x, result.eval());
	x = 1.;
	printf("x = %.2f: %.4f\n", x, result.eval());

	const int TIMES = 10000;
	timeExec<TIMES>("Bind evaluation", bind(&decltype(result)::eval, &result));
	timeExec<1>("Lambda evaluation", [&]() {
		for(int i = 0; i < TIMES; ++i) {
			result.eval();
		}
		return result.eval();
	});
}
