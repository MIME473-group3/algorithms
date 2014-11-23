/*
 * LinkedList.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: adam
 */

#include "LinkedList.h"
#include <iostream>

void LinkedList::deleteList(Node* node) {
	if(node != nullptr) {
		deleteList(node->next_);
		node->next_ = nullptr;
		delete node;
		--size_;
	}
}

void LinkedList::push_front(int data) {
	Node* node = new Node(data);
	node->next_ = root_;
	root_ = node->next_;
	++size_;
}

void LinkedList::push_back(int data) {
	if(isEmpty()) {
		push_front(data);
		return;
	}

	Node* node = root_;
	while(node->next_) {
		node = node->next_;
	}

	node->next_ = new Node(data);
	++size_;
}

bool LinkedList::remove(int data) {
	if(isEmpty()) {
		return false;
	}

	Node* node = root_;
	if(root_->data_ == data) {
		root_ = root_->next_;
		delete node;
		--size_;
		return true;
	}

	while(node->next_) {
		if(node->next_->data_ == data) {
			Node* toDelete = node->next_;
			node->next_ = node->next_->next_;
			delete toDelete;
			--size_;
			return true;
		}
	}
	return false;
}


//	===	Non Class Functions	===========================================================================

int size(Node* head) {
	int size = 0;
	while(head) {
		++size;
		head = head->next;
	}
	return size;
}

Node* pad(Node* head, int n, int value) {
	while(n > 0) {
		Node* node = new Node(value);
		node->next = head;
		head = node;
		--n;
	}
	return head;
}

bool equal(Node* n1, Node* n2) {
	if(!n1 && !n2) {
		return true;
	}

	if(n1 && n2) {
		return n1->data == n2->data && equal(n1->next, n2->next);
	}

	return false; //one is nullptr
}

void print(Node* head) {
	while(head) {
		std::cout << head->data << " ";
		head = head->next;
	}
	std::cout << std::endl;
}
