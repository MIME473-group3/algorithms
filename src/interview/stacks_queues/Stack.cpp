/*
 * Stack.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: adam
 */

#include "Stack.h"
#include <iostream>

Stack::~Stack() {

	while(top_) {
		Node* node = top_;
		top_ = top_->next;
		delete node;
	}
}

void Stack::push(int data) {
	top_ = new Node(data, top_);
	++size_;
}

int Stack::pop() {
	int data = top_->data;
	Node* node = top_;
	top_ = top_->next;
	delete node;
	--size_;
	return data;
}

int Stack::peek() {
	return top_->data;
}

int Stack::size() {
	return size_;
}

bool Stack::empty() {
	return size_ == 0;
}

void Stack::print() {
	Node* node = top_;
	std::cout << "stack: ";
	while(node) {
		std::cout << node->data << " ";
		node = node->next;
	}
	std::cout << std::endl;
}
