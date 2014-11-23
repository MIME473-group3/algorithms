/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "LinkedList.h"

int doAdd(Node* n1, Node* n2) {
	if(n1 == nullptr) { //both are the same length, so n2 is also a nullptr and we're done
		return 0;
	}

	int carry = doAdd(n1->next, n2->next);
	n1->data += n2->data + carry;
	if(n1->data >= 10) {
		n1->data -= 10;
		carry = 1;
	} else {
		carry = 0;
	}
	return carry;
}

Node* recursiveAdd(Node* n1, Node* n2) {
	int s1 = size(n1);
	int s2 = size(n2);

	if(s1 > s2) {
		n2 = pad(n2, s1 - s2);
	} else if(s2 > s1) {
		n1 = pad(n1, s2 - s1);
	}

	int carry = doAdd(n1, n2);
	if(carry) {
		return pad(n1, 1, carry);
	}
	return n1;
}

struct AddOrderedListsTest : public testing::Test {


};


TEST_F(AddOrderedListsTest, EqualSizeTest) {

	Node* a = new Node(6, new Node(1, new Node(7)));
	Node* b = new Node(2, new Node(9, new Node(5)));
	Node* expectedResult = new Node(9, new Node(1, new Node(2)));

	print(a);
	print(b);
	print(expectedResult);

	Node* computedResult = recursiveAdd(a, b);
	print(computedResult);
	ASSERT_TRUE(equal(computedResult, expectedResult));

	b->erase();
	expectedResult->erase();
	computedResult->erase();

}

TEST_F(AddOrderedListsTest, 1shorterTest) {

	Node* a = new Node(6, new Node(1));
	Node* b = new Node(2, new Node(9, new Node(5)));
	Node* expectedResult = new Node(3, new Node(5, new Node(6)));

	print(a);
	print(b);
	print(expectedResult);

	Node* computedResult = recursiveAdd(a, b);
	print(computedResult);
	ASSERT_TRUE(equal(computedResult, expectedResult));

	b->erase();
	expectedResult->erase();
	computedResult->erase();

}

TEST_F(AddOrderedListsTest, 2shorterTest) {

	Node* a = new Node(9, new Node(8, new Node(8)));
	Node* b = new Node(1, new Node(2));
	Node* expectedResult = new Node(1, new Node(0, new Node(0, new Node(0))));

	print(a);
	print(b);
	print(expectedResult);

	Node* computedResult = recursiveAdd(a, b);
	print(computedResult);
	ASSERT_TRUE(equal(computedResult, expectedResult));

	b->erase();
	expectedResult->erase();
	computedResult->erase();

}

