/*
 * interpreter.cpp
 *
 *  Created on: Jul 20, 2014
 *      Author: Adam Kosiorek
 */

#include "interpreter.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	cout << "Hello World!" << endl;
	double x = 0;
	// sigmoid((2X + 3) * 2 + 1)
	AbstractExpr& result = sigmoid((literal(2.) * variable(x) + 3.) * literal(.25) + 1.);

	cout << "sigmoid((2x + 3) * 0.25 + 1) =" << endl;
	x = .25;
	printf("x = %.2f: %.4f\n", x, result.eval());
	x = .5;
	printf("x = %.2f: %.4f\n", x, result.eval());
	x = 1.;
	printf("x = %.2f: %.4f\n", x, result.eval());
	delete &result;


}
