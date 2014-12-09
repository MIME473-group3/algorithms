/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <glog/logging.h>

struct Node {

	const std::string key;
	int value;
	int sum;
	Node* parent;
	Node* left;
	Node* right;

	Node(const std::string& key, int value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
	: key(key), value(value), sum(value), parent(parent), left(left), right(right) {}
};

void deleteTree(Node* root) {
	if(!root) {
		return;
	}

	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}


bool insert(Node* root, const std::string& key, int value) {

	if(!root) {
		return false;
	}

	bool result = false;
	if(key <= root->key) {
		if(root->left) {
			result = insert(root->left, key, value);
		} else {
			root->left = new Node(key, value, root);
			result = true;
		}
	} else {
		if(root->right) {
			result = insert(root->right, key, value);
		} else {
			root->right = new Node(key, value, root);
			result = true;
		}
	}
	if(result) {
		root->sum += value;
	}
	return result;
}

Node* find(Node* root, const std::string& key) {
	if(!root) {
		return nullptr;
	}

	if(key == root->key) {
		return root;
	}
	if(key < root->key) {
		return find(root->left, key);
	}
	return find(root->right, key);
}


Node* lowestCommonAncestorHelper(Node* root, const std::string& key1, const std::string& key2) {
	if(!root) {
		return nullptr;
	}

	if(key1 < root->key && key2 < root->key) {
		return lowestCommonAncestorHelper(root->left, key1, key2);
	}

	if(key1 > root->key && key2 > root->key) {
		return lowestCommonAncestorHelper(root->right, key1, key2);
	}

	if(find(root, key1) && find(root, key2)) {
		return root;
	}

	return nullptr;
}

Node* lowestCommonAncestor(Node* root, const std::string& key1, const std::string& key2) {

	if(key1 == key2) {
		return find(root, key1);
	}
	return lowestCommonAncestorHelper(root, key1, key2);
}

int prefixSum(Node* root, Node* node) {

	int sum = 0;
	Node* current = node;
	while(current) {
		if(current->key <= node->key) {
			sum += current->value;
			if(current->left) {
				sum += current->left->sum;
			}
		}
		current = current->parent;
	}
	return sum;
}

int sumBetweenStrings(Node* root, std::string str1, std::string str2) {
	if(!root) {
		return 0;
	}

	if(str1 > str2) {
		std::swap(str1, str2);
	}

	Node* smaller = find(root, str1);
	Node* greater = find(root, str2);
	if(!smaller || !greater) {
		return 0;
	}

	return prefixSum(root, greater) - prefixSum(root, smaller) - greater->value;
}

struct PrefixSum {
	Node* lastNode;
	int sum;
	PrefixSum(Node* lastNode, int sum) : lastNode(lastNode), sum(sum) {}
};

PrefixSum prefixSumFind(Node* root, const std::string& key) {
	if(!root) {
		return PrefixSum(nullptr, 0);
	}

	if(root->key > key) {
		return prefixSumFind(root->left, key);
	}

	int sum = root->value;
	if(root->left) {
		sum += root->left->sum;
	}

	if(root->key == key) {
		return PrefixSum(root, sum);
	}

	PrefixSum result = prefixSumFind(root->right, key);
	result.sum += sum;
	return result;
}

int sumBetweenStringsWithoutParentLink(Node* root, std::string str1, std::string str2) {
	if(!root) {
		return 0;
	}

	if(str1 > str2) {
		std::swap(str1, str2);
	}

	auto smaller = prefixSumFind(root, str1);
	auto greater = prefixSumFind(root, str2);
	if(!smaller.lastNode || !greater.lastNode) {
		return 0;
	}

	return greater.sum - smaller.sum - greater.lastNode->value;
}


struct SumBetweenStringsTest : public testing::Test {

	void SetUp() {

		testTree = new Node("L", 0);

		insert(testTree, "H", 1);
		insert(testTree, "C", 4);
		insert(testTree, "K", 3);
		insert(testTree, "A", 1);
		insert(testTree, "D", 2);
		insert(testTree, "J", -1);
		insert(testTree, "P", 7);
		insert(testTree, "N", 1);
		insert(testTree, "T", 4);
		insert(testTree, "M", -1);
		insert(testTree, "O", -2);

		Utils::printTree(testTree, SumBetweenStringsTest::printNode);
	}

	void TearDown() {
		deleteTree(testTree);
	}

	static void printNode(Node* node) {
		std::cout << node->key << "=(" << node->value << "," << node->sum << ")";
	}

	Node* testTree;
};


TEST_F(SumBetweenStringsTest, WithParentLinkTest) {

	ASSERT_EQ(sumBetweenStrings(testTree, "L", "L"), 0);
	ASSERT_EQ(sumBetweenStrings(testTree, "H", "P"), 0);
	ASSERT_EQ(sumBetweenStrings(testTree, "A", "T"), 14);
	ASSERT_EQ(sumBetweenStrings(testTree, "D", "T"), 8);
	ASSERT_EQ(sumBetweenStrings(testTree, "A", "M"), 9);
	ASSERT_EQ(sumBetweenStrings(testTree, "D", "M"), 3);
	ASSERT_EQ(sumBetweenStrings(testTree, "A", "O"), 9);
}

TEST_F(SumBetweenStringsTest, WithoutParentLinkTest) {

	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "L", "L"), 0);
	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "H", "P"), 0);
	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "A", "T"), 14);
	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "D", "T"), 8);
	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "A", "M"), 9);
	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "D", "M"), 3);
	ASSERT_EQ(sumBetweenStringsWithoutParentLink(testTree, "A", "O"), 9);
}

