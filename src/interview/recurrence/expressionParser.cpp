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
	const map<char, char> openingBrackets;
	const map<char, char> closingBrackets;
	set<char> symbols;
	const char errorCode = '\0';

public:
	ExpressionParser(const set<char>& operands, const map<char, OpType>& operators, const map<char, char>& openingBrackets,
			const map<char, char>& closingBrackets)
		: operands(operands), operators(operators), openingBrackets(openingBrackets), closingBrackets(closingBrackets) {

		for(char c : operands) {
			symbols.insert(c);
		}
		for(auto& entry : operators) {
			symbols.insert(entry.first);
		}

		addBracketsToSymbolsAndCheck(openingBrackets, closingBrackets, "There is no matching closing bracket for ");
		addBracketsToSymbolsAndCheck(closingBrackets, openingBrackets, "There is no matching opening bracket for ");

	}

	char parseExpression(const std::string& expr) {
		if(expr.empty()) {
			return errorCode;
		}
		stack<char> front;
		stack<char> back;
		for(auto it = expr.rbegin(); it != expr.rend(); ++it) {
			if(!contains(symbols, *it)) {
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
		moveOpeningBrackets(front, back);

		char op2 = checkAndPopOp(front);
		OpType fun = operators.at(front.top());
		front.pop();
		while(contains(openingBrackets, front.top())) {
			parseExpression(front, back);
		}
		char op1 = checkAndPopOp(front);
		eraseRedundantBrackets(front, back);
		front.push(fun(op1, op2));
		if(front.size() != 1) {
			parseExpression(front, back);
		}
	}

private:
	void moveOpeningBrackets(stack<char>& front, stack<char>& back) {
		while(!front.empty() && contains(openingBrackets, front.top())) {
			back.push(front.top());
			front.pop();
		}
	}

	void eraseRedundantBrackets(stack<char>& front, stack<char>& back) {
		while(!front.empty() && !back.empty() && contains(closingBrackets, front.top()) && closingBrackets.at(front.top()) == back.top()) {
			front.pop();
			back.pop();
		}
	}

	char checkAndPopOp(stack<char>& s) {
		char c = -1;
		if(contains(operands, s.top())) {
			c = s.top();
			s.pop();
		}
		return c;
	}

	void addBracketsToSymbolsAndCheck(const map<char, char>& from, const map<char, char>& to, const std::string& errorMessage) {
		for(auto& entry : from) {
			if(!contains(to, entry.second)) {
				throw new std::logic_error(errorMessage + entry.first);
			}
			symbols.insert(entry.first);
		}
	}

	template<class T>
	bool contains(const T& container, typename T::key_type key) {
		return container.find(key) != container.end();
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
		openingBrackets{{'(', ')'}, {'{', '}'}},
		closingBrackets{{')', '('}, {'}', '{'}},
		parser(operands, operators, openingBrackets, closingBrackets) {}

	const set<char> operands;
	const map<char, char(*)(char, char)> operators;
	const map<char, char> openingBrackets;
	const map<char, char> closingBrackets;
	ExpressionParser parser;
};


TEST_F(WaysOfParentesisingTest, SomeTest) {

	ASSERT_EQ(parser.parseExpression("1|0"), '1');
	ASSERT_EQ(parser.parseExpression("1&0"), '0');
	ASSERT_EQ(parser.parseExpression("1^0"), '1');
	ASSERT_EQ(parser.parseExpression("(1|0)"), '1');

	ASSERT_EQ(parser.parseExpression("1&(1|0)"), '1');
	ASSERT_EQ(parser.parseExpression("{1^(1|0)}"), '0');

	ASSERT_EQ(parser.parseExpression("1^0|0|1"), '1');
	ASSERT_EQ(parser.parseExpression("1^({0|0}|1)"), '0');
	ASSERT_EQ(parser.parseExpression("1^{0|(0|1)}"), '0');
}

