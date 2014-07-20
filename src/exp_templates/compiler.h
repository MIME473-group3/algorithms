/*
 * compiler.h
 *
 *  Created on: Jul 20, 2014
 *      Author: Adam Kosiorek
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include <cmath>
#include <functional>


template<class ExprType, bool isNumeric>
struct ExprTypeTrait {
	typedef ExprType Type;
};

class Constant;

template<class ExprType>
struct ExprTypeTrait<ExprType, true> {
	typedef Constant Type;
};

template<class Expr>
struct ExprType {
	typedef typename ExprTypeTrait<Expr, std::is_arithmetic<Expr>::value>::Type Type;
};

template<class Exp1, class Exp2, class Op>
class BinaryExpr {
	typename ExprType<Exp1>::Type exp1_;
	typename ExprType<Exp2>::Type exp2_;
	Op op_;
public:
	BinaryExpr(Exp1 exp1, Exp2 exp2) : exp1_(exp1), exp2_(exp2) {};
	double eval() const { return op_(exp1_.eval(), exp2_.eval()); };
};

template<class Exp, class Op>
class UnaryExpr {
	typename ExprType<Exp>::Type exp_;
	Op op_;
public:
	UnaryExpr(Exp exp) : exp_(exp) {};
	double eval() const { return op_(exp_.eval()); };
};

class Variable {
	double& v_;
public:
	Variable(double& v) : v_(v) {};
	double eval() const { return v_; };
};

class Constant {
	double c_;
public:
	Constant(const double c) : c_(c) {};
	double eval() const { return c_; };
};

//	Operators	=========================================================================

struct Sigmoid {
	double operator() (double x) const {
		return 1 / (1 + exp(-x));
	}
};

template<class Exp>
UnaryExpr<Exp, Sigmoid> sigmoid(const Exp& exp) {
	return UnaryExpr<Exp, Sigmoid>(exp);
}



template<class Exp1, class Exp2>
BinaryExpr<Exp1, Exp2, std::plus<double>> operator+(const Exp1& exp1, const Exp2 exp2) {
	return BinaryExpr<Exp1, Exp2, std::plus<double>>(exp1, exp2);
};

template<class Exp1, class Exp2>
BinaryExpr<Exp1, Exp2, std::minus<double>> operator-(const Exp1& exp1, const Exp2 exp2) {
	return BinaryExpr<Exp1, Exp2, std::minus<double>>(exp1, exp2);
};

template<class Exp1, class Exp2>
BinaryExpr<Exp1, Exp2, std::multiplies<double>> operator*(const Exp1& exp1, const Exp2 exp2) {
	return BinaryExpr<Exp1, Exp2, std::multiplies<double>>(exp1, exp2);
};

template<class Exp1, class Exp2>
BinaryExpr<Exp1, Exp2, std::divides<double>> operator/(const Exp1& exp1, const Exp2 exp2) {
	return BinaryExpr<Exp1, Exp2, std::divides<double>>(exp1, exp2);
};




#endif /* COMPILER_H_ */
