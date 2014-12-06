/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <set>
#include <algorithm>

std::vector<long> seq357(long k) {
	std::vector<long> seq;
	std::set<long> q;
	q.insert(1);
	--k;
	long current;
	while(k > 0) {
		auto it = std::min_element(q.begin(), q.end());
		current = *it;
		q.erase(it);

		seq.push_back(current);
		q.insert(3 * current);
		q.insert(5 * current);
		q.insert(7 * current);
		--k;
	}

	return seq;
}

struct Seq357Test : public testing::Test {


};


TEST_F(Seq357Test, SomeTest) {

	Utils::printVec(seq357(10000));
}

