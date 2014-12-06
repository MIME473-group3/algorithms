/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <stack>
#include <algorithm>
#include <random>
#include <map>
#include <glog/logging.h>

struct Box {
	float width;
	float height;
	float depth;

	Box() : width(0), height(0), depth(0) {}
	Box(float w, float h, float d)
	: width(w), height(h), depth(d) {}

	bool operator<(const Box& other) const {
		return width < other.width && height < other.height && depth < other.depth;
	}

	bool operator>(const Box& other) const {
		return other < *this;
	}

	bool operator== (const Box& other) const {
		return !(*this < other) && !(*this > other);
	}
};

std::pair<int, int> getNextBiggest(const std::vector<Box>& boxes, int start) {
	if(start >= boxes.size()) {
		return std::make_pair(boxes.size(), boxes.size());
	}

	if(boxes.size() == 1) {
		return std::make_pair(0, 1);
	}

	int maxIndex = start;
	++start;
	while(start < boxes.size() && !(boxes[maxIndex] > boxes[start])) {
		if(boxes[maxIndex].height < boxes[start].height) {
			maxIndex = start;
		}
		++start;
	}
	return std::make_pair(maxIndex, start);
}

std::pair<std::stack<Box>, float> buildStack(std::vector<Box>& boxes) {
	std::stack<Box> result;
	float height = 0;

	std::sort(boxes.begin(), boxes.end(), std::greater<Box>());

	auto index = getNextBiggest(boxes, 0);
	while(index.first < boxes.size()) {

		Box& box = boxes[index.first];
		LOG(ERROR) << index.first << " " << box.height;
		height += box.height;
		result.push(box);
		index = getNextBiggest(boxes, index.second);
	}

	return std::make_pair(result, height);
}

std::pair<std::vector<Box>, float> buildStackR(const std::vector<Box>& boxes, std::vector<Box>& current, int index) {
	std::vector<Box> maxStack;
	float maxHeight = std::numeric_limits<float>::min();

	for(int i = 0; i < boxes.size(); ++i) {
		if(index == 0 || boxes[i] < current[index - 1]) {
			current[index] = boxes[i];
			auto result = buildStackR(boxes, current, index + 1);
			float currentHeight = result.second;
			auto& currentStack = result.first;
			if(currentHeight > maxHeight) {
				maxHeight = currentHeight;
				maxStack = currentStack;
			}
		}
	}

	if(maxStack.empty()) {
		maxHeight = 0;
		maxStack = current;
		maxStack.resize(index);
		for(auto box : maxStack) {
			maxHeight += box.height;
		}
	}

	return std::make_pair(maxStack, maxHeight);
}

std::pair<std::stack<Box>, float> buildStackR(const std::vector<Box>& boxes) {

	std::vector<Box> current(boxes.size());
	auto resultPair = buildStackR(boxes, current, 0);
	auto& resultVec = resultPair.first;
	std::stack<Box> result;
	LOG(ERROR) << "R:" << resultVec.size();
	for(auto it = resultVec.rbegin(); it != resultVec.rend(); ++it) {
		result.push(*it);
	}
	return std::make_pair(result, resultPair.second);
}

float computeHeight(const std::vector<Box>& boxes) {
	float height = 0;
	for(const auto& box : boxes) {
		height += box.height;
	}
	return height;
}

struct StackOfBoxesTest : public testing::Test {

	StackOfBoxesTest() : boxes1{
							Box(3, 4, 5),
							Box(4, 5, 3),
							Box(10, 8, 7),
							Box(1, 1, 1),
							Box(5, 3, 4)
						}, boxes2{
							Box(3, 4, 5),
							Box(4, 5, 3),
							Box(10, 8, 7),
							Box(1, 1, 1),
							Box(5, 3, 4),
							Box(0.4, 0.5, 0.3),
							Box(0.3, 0.4, 0.5),
							Box(0.5, 0.4, 0.3)
						},
						expectedHeight1(14),
						expectedHeight2(14.5) {

							expectedStack1.push(boxes1[2]);
							expectedStack1.push(boxes1[1]);
							expectedStack1.push(boxes1[4]);

							expectedStack2.push(boxes2[2]);
							expectedStack2.push(boxes2[1]);
							expectedStack2.push(boxes2[4]);
							expectedStack2.push(boxes2[5]);
						}

	std::vector<Box> boxes1;
	std::vector<Box> boxes2;
	std::stack<Box> expectedStack1;
	std::stack<Box> expectedStack2;
	float expectedHeight1, expectedHeight2;
};


TEST_F(StackOfBoxesTest, IterativeSolutionTest) {


	auto result = buildStack(boxes1);
	ASSERT_EQ(result.first.size(), expectedStack1.size());
	ASSERT_EQ(result.second, expectedHeight1);


	result = buildStack(boxes2);
	ASSERT_EQ(result.first.size(), expectedStack2.size());
	ASSERT_EQ(result.second, expectedHeight2);
}

TEST_F(StackOfBoxesTest, RecursiveSolutionTest) {


	auto result = buildStackR(boxes1);
	ASSERT_EQ(result.first.size(), expectedStack1.size());
	ASSERT_EQ(result.second, expectedHeight1);


	result = buildStackR(boxes2);
	ASSERT_EQ(result.first.size(), expectedStack2.size());
	ASSERT_EQ(result.second, expectedHeight2);
}

//TODO
TEST_F(StackOfBoxesTest, DISABLED_DynamicProgSolutionTest) {


//	auto result = buildStackDP(boxes1);
//	ASSERT_EQ(result.first.size(), expectedStack1.size());
//	ASSERT_EQ(result.second, expectedHeight1);
//
//
//	result = buildStackDP(boxes2);
//	ASSERT_EQ(result.first.size(), expectedStack2.size());
//	ASSERT_EQ(result.second, expectedHeight2);
}

