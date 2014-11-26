/*
 * Stack.h
 *
 *  Created on: Nov 26, 2014
 *      Author: adam
 */

#ifndef INTERVIEW_STACKS_QUEUES_STACK_H_
#define INTERVIEW_STACKS_QUEUES_STACK_H_


class Stack {
	struct Node {
		Node* next;
		int data;
		Node(int data, Node* next = nullptr) : data(data), next(next) {}
	};

	Node* top_;
	int size_;
public:
	Stack() : top_(nullptr), size_(0) {}
	~Stack();

	void push(int data);
	int pop();
	int peek();
	int size();
	bool empty();
	void print();
};

#endif /* INTERVIEW_STACKS_QUEUES_STACK_H_ */
