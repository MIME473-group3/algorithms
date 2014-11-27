/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include <trees_graphs/Graph.h>
#include "gtest/gtest.h"
#include "Utils.h"

std::pair<bool, int> computeBalance(TreeNode* node) {
	if(!node) {
		return std::make_pair(true, 0);
	}

	auto left = computeBalance(node->left);
	auto right = computeBalance(node->right);

	int height = 1 + std::max(left.second, right.second);
	bool balanced = left.first && right.first && abs(left.second - right.second) < 2;
	return std::make_pair(balanced, height);
}

bool isBalanced(TreeNode* root) {
	if(!root) {
		return true;
	}

	return computeBalance(root).first;
}

struct IsTreeBalancedTest : public testing::Test {


};

TEST_F(IsTreeBalancedTest, BalancedTest) {

	TreeNode* balanced = new TreeNode(0, new TreeNode(0, new TreeNode(0), new TreeNode(0)), new TreeNode(0, new TreeNode(0, new TreeNode(0)), new TreeNode(0)));
	ASSERT_TRUE(isBalanced(balanced));
}

TEST_F(IsTreeBalancedTest, UnbalancedTest) {
	TreeNode* unbalanced =
			new TreeNode(0,
				new TreeNode(0,
						new TreeNode(0),
						new TreeNode(0,
								new TreeNode(0,
										new TreeNode(0,
												new TreeNode(0,
														new TreeNode(0)
															)
													)
											)
									)
							),
				new TreeNode(0,
						new TreeNode(0,
								new TreeNode(0)
									),
						new TreeNode(0)
							)
						);


	ASSERT_FALSE(isBalanced(unbalanced));
}

