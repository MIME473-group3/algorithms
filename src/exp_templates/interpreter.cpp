/*
 * interpreter.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: Adam Kosiorek
 */

#include "interpreter.h"
#include "utils.h"
#include <iostream>
#include <functional>

using namespace std;

int main(int argc, char** argv) {

	cout << "Hello World!" << endl;
	double x = 0;
	// sigmoid((2X + 3) * 2 + 1)
	AbstractExpr& result = 	sigmoid((2 * variable(x) + 3) * 0.25 + 1);


	cout << "sigmoid((2x + 3) * 0.25 + 1) =" << endl;
	x = .25;
	printf("x = %.2f: %.4f\n", x, result.eval());
	x = .5;
	printf("x = %.2f: %.4f\n", x, result.eval());
	x = 1.;
	printf("x = %.2f: %.4f\n", x, result.eval());

	const int TIMES = 10000;
	timeExec<TIMES>("Run-time evaluation", bind(&AbstractExpr::eval, &result));
	timeExec<1>("Run-time evaluation", [&]() {
		for(int i = 0; i < TIMES; ++i) {
			result.eval();
		}
		return result.eval();
	});


	delete &result;
}
