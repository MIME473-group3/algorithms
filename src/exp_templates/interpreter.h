/*
 * interpreter.h
 *
 *  Created on: Jul 20, 2014
 *      Author: Adam Kosiorek
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <cmath>
#include <stdexcept>
#include <type_traits>

class AbstractExpr {
public:
	virtual double eval() const = 0;
	virtual ~AbstractExpr() = default;
};

class TerminalExpr : public AbstractExpr {};

class Literal : public TerminalExpr {
	const double c_;
public:
	Literal(const double c) : c_(c) {};
	virtual double eval() const { return c_; }
};

class Variable : public TerminalExpr {
	double& v_;
public:
	Variable(double& v) : v_(v) {};
	virtual double eval() const { return v_; }
};

class NonTerminalExpr : public AbstractExpr {};

//	Unary Expressions	=================================================================

class UnaryExpr : public NonTerminalExpr {
protected:
	const AbstractExpr* e_;
public:
	UnaryExpr(const AbstractExpr* e) : e_(e) {};
	virtual ~UnaryExpr() { delete const_cast<AbstractExpr*>(e_); };
};

class Sigmoid : public UnaryExpr {
public:
	Sigmoid(const AbstractExpr* e) : UnaryExpr(e) {};
	virtual double eval() const { return 1 / (1 + exp(- this->e_->eval())); }
};

//	Binary Expressions	=================================================================

class BinaryExpr : public NonTerminalExpr {
protected:
	const AbstractExpr* e1_;
	const AbstractExpr* e2_;
public:
	BinaryExpr(const AbstractExpr* e1, const AbstractExpr* e2) : e1_(e1), e2_(e2) {};
	virtual ~BinaryExpr() {
		delete const_cast<AbstractExpr*>(e1_);
		delete const_cast<AbstractExpr*>(e2_);
	}
};

class Product : public BinaryExpr {
public:
	Product(const AbstractExpr* e1, const AbstractExpr* e2) : BinaryExpr(e1, e2) {};
	virtual double eval() const { return this->e1_->eval() * this->e2_->eval(); }
};

class Quotient : public BinaryExpr {
public:
	Quotient(const AbstractExpr* e1, const AbstractExpr* e2) : BinaryExpr(e1, e2) {};
	virtual double eval() const {
		double second = this->e2_->eval();
		if(second == 0.) throw new std::invalid_argument("Division by 0");
		return this->e1_->eval() / second;
	}
};

class Sum : public BinaryExpr {
public:
	Sum(const AbstractExpr* e1, const AbstractExpr* e2) : BinaryExpr(e1, e2) {};
	virtual double eval() const { return this->e1_->eval() + this->e2_->eval(); }
};

class Difference : public BinaryExpr {
public:
	Difference(const AbstractExpr* e1, const AbstractExpr* e2) : BinaryExpr(e1, e2) {};
	virtual double eval() const { return this->e1_->eval() - this->e2_->eval(); }
};


//	Operators	=========================================================================

Sum& operator+(const AbstractExpr& e1, const AbstractExpr& e2) {
	return *new Sum(&e1, &e2);
}

Difference& operator-(const AbstractExpr& e1, const AbstractExpr& e2) {
	return *new Difference(&e1, &e2);
}

Product& operator*(const AbstractExpr& e1, const AbstractExpr& e2) {
	return *new Product(&e1, &e2);
}

Quotient& operator/(const AbstractExpr& e1, const AbstractExpr& e2) {
	return *new Quotient(&e1, &e2);
}

//template<class T>
//Sum& operator+(const AbstractExpr& e1, const T& t) {
////	static_assert(std::is_arithmetic<T>::value, "Implemented for arithmetic types only");
//	return *new Sum(&e1, new Literal(t));
//}

//template<>
//Sum& operator+<AbstractExpr>(const AbstractExpr& e1, const AbstractExpr& e2) {
//	return *new Sum(&e1, &e2);
//}

//	Helper functions	=================================================================

Variable& variable(double& x) {
	return *(new Variable(x));
}

Literal& literal(double c) {
	return *(new Literal(c));
}

Sigmoid& sigmoid(const AbstractExpr& e) {
	return *(new Sigmoid(&e));
}

//	=====================================================================================


#endif /* INTERPRETER_H_ */
