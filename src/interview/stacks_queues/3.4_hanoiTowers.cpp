/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "Stack.h"

struct HanoiTowers {
	std::vector<Stack> towers;
	int height;

	HanoiTowers(int n, int m) : towers(n), height(m) {
		for(int i = m; i > 0; --i) {
			towers[0].push(i);
		}
	}

	bool solved() {
		for(int i = 0; i < towers.size() - 2; ++i) {
			if(!towers[i].empty()) {
				return false;
			}
		}

		Stack& tower = towers[towers.size() - 1];
		int prev = tower.pop();
		while(!tower.empty()) {
			if(tower.peek() <= prev) {
				return false;
			}
			prev = tower.pop();
		}
		return true;
	}


	void moveRight(int n) {
//		print();
		if(n == 1) {
			for(int i = 1; i < towers.size(); ++i) {
				towers[i].push(towers[i - 1].pop());
			}
		} else if(n != 0){
			moveRight(n - 1);
			towers[1].push(towers[0].pop());
			moveLeft(n - 1);
			towers[2].push(towers[1].pop());
			moveRight(n - 1);
		}
	}

	void moveLeft(int n) {
//		print();
		if(n == 1) {
			for(int i = towers.size() - 1; i > 0; --i) {
				towers[i - 1].push(towers[i].pop());
			}
		} else if(n != 0) {
			moveLeft(n - 1);
			towers[1].push(towers[2].pop());
			moveRight(n - 1);
			towers[0].push(towers[1].pop());
			moveLeft(n - 1);
		}
	}

		void print() {

			for(auto& tower : towers) {
				tower.print();
			}
		}

		void solve() {
			moveRight(height);
		}
};

struct Test : public testing::Test {


};


TEST_F(Test, SomeTest) {

	HanoiTowers tower(3, 15);
	tower.print();
	tower.solve();
	tower.print();
	ASSERT_TRUE(tower.solved());
}

