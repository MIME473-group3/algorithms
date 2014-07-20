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

template<bool isExpr, class T>
struct Converter {
	static const AbstractExpr* convert(const T& t) {
		return &t;
	}
};

template<class T>
struct Converter<false, T> {
	static const AbstractExpr* convert(const T& t) {
		static_assert(std::is_convertible<T, double>::value, "Type must be convertible to double");
		return new Literal(t);
	}
};

template<class T>
const AbstractExpr* convert(const T& t) {
	return Converter<std::is_base_of<AbstractExpr, T>::value, T>::convert(t);
}




template<class A, class B>
AbstractExpr& operator+(const A& a, const B& b) {

	return *new Sum(convert<A>(a), convert<B>(b));
}

template<class A, class B>
AbstractExpr& operator-(const A& a, const B& b) {

	return *new Difference(convert<A>(a), convert<B>(b));
}

template<class A, class B>
AbstractExpr& operator*(const A& a, const B& b) {

	return *new Product(convert<A>(a), convert<B>(b));
}

template<class A, class B>
AbstractExpr& operator/(const A& a, const B& b) {

	return *new Quotient(convert<A>(a), convert<B>(b));
}

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
