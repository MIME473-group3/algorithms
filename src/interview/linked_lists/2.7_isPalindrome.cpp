/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "LinkedList.h"

bool isPalindromeIterative(Node* head) {
	int listSize = size(head);
	int i = listSize / 2;
	Node* reversed;
	while(i > 0) {
		reversed = new Node(head->data, reversed);
		head = head->next;
		--i;
	}
	if(listSize % 2 == 1) { // odd number of elements; skip the middle one
		head = head->next;
	}
	while(head) {
		if(head->data != reversed->data) {
			return false;
		}
		head = head->next;
		reversed = reversed->next;
	}
	return true;
}

bool isPalindromeRecursiveImpl(Node** head, Node* current) {
	if(!current) {
		return true;
	}
	if(!isPalindromeRecursiveImpl(head, current->next)) {
		return false;
	}
	bool result = (*head)->data == current->data;
	*head = (*head)->next;
	return result;
}

bool isPalindromeRecursive(Node* head) {
	return isPalindromeRecursiveImpl(&head, head);
}

struct Test : public testing::Test {

	void SetUp() {

		positiveOdd = new Node(1, new Node(2, new Node(3, new Node(2, new Node(1)))));
		positiveEven = new Node(1, new Node(2, new Node(2, new Node(1))));
		negativeOdd = new Node(1, new Node(2, new Node(3, new Node(4))));
		negativeEven = new Node(1, new Node(2, new Node(3, new Node(4, new Node(5)))));
	}

	void TearDown() {
		positiveOdd->erase();
		positiveEven->erase();
		negativeOdd->erase();
		negativeEven->erase();
	}

	Node* positiveOdd;
	Node* positiveEven;
	Node* negativeOdd;
	Node* negativeEven;
};

TEST_F(Test, IterativeTest) {

	ASSERT_TRUE(isPalindromeIterative(positiveOdd));
	ASSERT_TRUE(isPalindromeIterative(positiveEven));
	ASSERT_FALSE(isPalindromeIterative(negativeOdd));
	ASSERT_FALSE(isPalindromeIterative(negativeEven));
}

TEST_F(Test, RecursiveTest) {

	ASSERT_TRUE(isPalindromeRecursive(positiveOdd));
	ASSERT_TRUE(isPalindromeRecursive(positiveEven));
	ASSERT_FALSE(isPalindromeRecursive(negativeOdd));
	ASSERT_FALSE(isPalindromeRecursive(negativeEven));
}

