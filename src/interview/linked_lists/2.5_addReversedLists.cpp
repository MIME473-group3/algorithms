/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "LinkedList.h"

void recursiveAdd(Node* n1, Node* n2, int carry = 0) {
	n1->data += n2->data + carry;
	if(n1->data >= 10) {
		n1->data -= 10;
		carry = 1;
	} else {
		carry = 0;
	}

	if(n2->next) {
		if(!n1->next) {
			n1->next = new Node(0);
		}
		recursiveAdd(n1->next, n2->next, carry);
	} else if(carry > 0) {
		if(n1->next) {
			Node* tmpNode = new Node(carry);
			recursiveAdd(n1->next, tmpNode);
			delete tmpNode;
		} else {
			n1->next = new Node(carry);
		}
	}
}

struct AddReversedListsTest : public testing::Test {


};


TEST_F(AddReversedListsTest, EqualSizeTest) {

	Node* a = new Node(7, new Node(1, new Node(6)));
	Node* b = new Node(5, new Node(9, new Node(2)));
	Node* expectedResult = new Node(2, new Node(1, new Node(9)));

	print(a);
	print(b);
	print(expectedResult);

	recursiveAdd(a, b);
	print(a);
	ASSERT_TRUE(equal(a, expectedResult));

	b->erase();
	expectedResult->erase();
	a->erase();

}

TEST_F(AddReversedListsTest, 1shorterTest) {

	Node* a = new Node(1, new Node(6));
	Node* b = new Node(5, new Node(9, new Node(2)));
	Node* expectedResult = new Node(6, new Node(5, new Node(3)));

	print(a);
	print(b);
	print(expectedResult);

	recursiveAdd(a, b);
	print(a);
	ASSERT_TRUE(equal(a, expectedResult));

	b->erase();
	expectedResult->erase();
	a->erase();

}

TEST_F(AddReversedListsTest, 2shorterTest) {

	Node* a = new Node(8, new Node(8, new Node(9)));
	Node* b = new Node(2, new Node(1));
	Node* expectedResult = new Node(0, new Node(0, new Node(0, new Node(1))));

	print(a);
	print(b);
	print(expectedResult);

	recursiveAdd(a, b);
	print(a);
	ASSERT_TRUE(equal(a, expectedResult));

	b->erase();
	expectedResult->erase();
	a->erase();

}
