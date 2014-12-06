/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <stack>
#include <set>
#include <map>
#include <glog/logging.h>

using namespace std;

class ExpressionParser {
	typedef char(*OpType)(char, char);
	const set<char> operands;
	const map<char, OpType> operators;
	const map<char, char> brackets;
	set<char> symbols;

public:
	ExpressionParser(const set<char>& operands, const map<char, OpType>& operators, const map<char, char>& brackets)
		: operands(operands), operators(operators), brackets(brackets) {

		for(char c : operands) {
			symbols.insert(c);
		}
		for(auto& entry : operators) {
			symbols.insert(entry.first);
		}
		for(auto& entry : brackets) {
			symbols.insert(entry.first);
		}
	}

	char parseExpression(const std::string& expr) {
		if(expr.empty()) {
			return '\0';
		}
		stack<char> front;
		stack<char> back;
		for(auto it = expr.rbegin(); it != expr.rend(); ++it) {
			if(symbols.find(*it) == symbols.end()) {
				throw new runtime_error("Illegal expression: " + *it);
			}
			front.push(*it);
		}

		parseExpression(front, back);
		char result = front.top();
		front.pop();
		return result;
	}

	void parseExpression(stack<char>& front, stack<char>& back) {
		if(front.empty() && back.empty()) {
			return;
		}
		moveBrackets(front, back);

		char op2 = checkAndPopOp(front);
		OpType fun = operators.at(front.top());
		front.pop();
		while(brackets.find(front.top()) != brackets.end()) {
			parseExpression(front, back);
		}
		char op1 = checkAndPopOp(front);
		moveBrackets(front, back);
		front.push(fun(op1, op2));
		if(front.size() != 1) {
			parseExpression(front, back);
		}
	}

private:
	void moveBrackets(stack<char>& front, stack<char>& back) {
		while(!front.empty() && brackets.find(front.top()) != brackets.end()) {
			back.push(front.top());
			front.pop();
		}
	}

	char checkAndPopOp(stack<char>& s) {
		char c = -1;
		if(operands.find(s.top()) != operands.end()) {
			c = s.top();
			s.pop();
		}
		return c;
	}
};

struct WaysOfParentesisingTest : public testing::Test {

	static char alternative(char c1, char c2) {
		if(c1 == '1' || c2 == '1') {
			return '1';
		}
		return '0';
	}

	static char conjunction(char c1, char c2) {
		if(c1 == '1' && c2 == '1') {
			return '1';
		}
		return '0';
	}

	static char exlusiveOr(char c1, char c2) {
		if((c1 == '1' && c2 == '0') || (c1 == '0' && c2 == '1')) {
			return '1';
		}
		return '0';
	}

	WaysOfParentesisingTest() :
		operands{'0', '1'},
		operators{{'|', alternative}, {'&', conjunction}, {'^', exlusiveOr}},
		brackets{{'(', ')'}, {')', '('}},
		parser(operands, operators, brackets){}

	const set<char> operands;
	const map<char, char(*)(char, char)> operators;
	const map<char, char> brackets;
	ExpressionParser parser;
};


TEST_F(WaysOfParentesisingTest, SomeTest) {

	ASSERT_EQ(parser.parseExpression("1|0"), '1');
	ASSERT_EQ(parser.parseExpression("1&0"), '0');
	ASSERT_EQ(parser.parseExpression("1^0"), '1');
	ASSERT_EQ(parser.parseExpression("(1|0)"), '1');

	ASSERT_EQ(parser.parseExpression("1&(1|0)"), '1');
	ASSERT_EQ(parser.parseExpression("1^(1|0)"), '0');

	ASSERT_EQ(parser.parseExpression("1^0|0|1"), '1');
	ASSERT_EQ(parser.parseExpression("1^((0|0)|1)"), '0');
	ASSERT_EQ(parser.parseExpression("1^(0|(0|1))"), '0');
}

