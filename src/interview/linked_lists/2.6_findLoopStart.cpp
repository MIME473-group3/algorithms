/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "LinkedList.h"

Node* findLoopStart(Node* head) {
	if(head == nullptr) {
		return head;
	}

	Node* slow = head;
	Node* fast = head;
	while(fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast) {
			break;
		}
	}
	if(!fast || !fast->next) { //list ended
		return nullptr;
	}
	/**
	 * say loop start is k elements from the head and the loop size is M; slow made k steps and is 0 steps in the loop,
	 * while fast made 2k steps and is k steps in the loop. It means that fast is r = k % M elements in the loop. Now, slow
	 * and fast will meet after additional M - r steps. Since slow was 0 elements in the loop, the runners will meet r elements
	 * before the start of the loop.
	 *
	 * Now when we start moving from the head and from the meeting point at rate 1 node per iteration, both runners
	 * will meet at the start of the loop.
	 * TODO I don't really get it. Why?
	 */

	while(head != slow) {
		head = head->next;
		slow = slow->next;
	}
	return head;
}

struct FindLoopStartTest : public testing::Test {

};


TEST_F(FindLoopStartTest, LoopTest) {

	Node* lastInLoop = new Node(0);
	Node* loopStart = new Node(1, new Node(0, new Node(0, new Node(0, lastInLoop))));
	lastInLoop->next = loopStart;

	Node* head = new Node(0, new Node(0, new Node(0, loopStart)));
	ASSERT_EQ(findLoopStart(head), loopStart);

	lastInLoop->next = nullptr;
	head->erase();

}

TEST_F(FindLoopStartTest, NoLoopTest) {

	Node* head = new Node(0, new Node(0, new Node(0, new Node(1, new Node(0, new Node(0, new Node(0)))))));
	ASSERT_EQ(findLoopStart(head), nullptr);
	head->erase();
}

