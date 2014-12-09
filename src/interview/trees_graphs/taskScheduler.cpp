/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include <map>
#include <list>
#include <stack>
#include <glog/logging.h>

class DiSymbolGraph {
	std::map<std::string, int> symbolMap;
	std::vector<std::string> vertices;
	std::vector<std::list<int>> adjacent;

public:
	bool exists(const std::string& symbol) {
		return symbolMap.find(symbol) != symbolMap.end();
	}

	bool addVertex(const std::string& symbol) {
		if(exists(symbol)) {
			return false;
		}

		symbolMap.emplace(symbol, symbolMap.size());
		vertices.push_back(symbol);
		adjacent.resize(adjacent.size() + 1);
	}

	bool addEdge(const std::string& from, const std::string& to) {
		addVertex(from);
		addVertex(to);

		adjacent[symbolMap[from]].push_back(symbolMap[to]);
	}

	std::vector<std::string> topologicalSort() {
		std::vector<int> group(vertices.size(), -1);
		std::stack<int> sortStack;
		std::vector<std::string> result;

		for(int i = 0; i < vertices.size(); ++i) {
			if(!topSortDFS(sortStack, group, i, i)) {
				return result;
			}
		}

		while(!sortStack.empty()) {
			result.push_back(vertices[sortStack.top()]);
			sortStack.pop();
		}
		return result;
	}

	bool topSortDFS(std::stack<int>& sortStack, std::vector<int>& group, int source, int groupID) {
		LOG(ERROR) << vertices[source];
		if(group[source] != -1) {
			if(group[source] == groupID) { //we've found a cycle!
				for(int v : adjacent[source]) {
					if(group[v] == groupID) {
						return false;
					}
				}
			}
			return true; //we've been there!
		}
		group[source] = groupID;

		for(int v : adjacent[source]) {
			if(!topSortDFS(sortStack, group, v, groupID)) {
				return false; //we've found a cycle!
			}
		}
		sortStack.push(source);
		return true;
	}
};

std::vector<std::string> schedule(const std::list<std::pair<std::string, std::string>>& constraints) {

	DiSymbolGraph graph;
	for(const auto& edge : constraints) {
		graph.addEdge(edge.first, edge.second);
	}
	return graph.topologicalSort();
}


struct TaskSchedulerTest : public testing::Test {};


TEST_F(TaskSchedulerTest, SomeTest) {

	std::list<std::pair<std::string, std::string>> constraints = {
			{"A", "B"},
			{"B", "E"},
			{"C", "D"},
			{"A", "C"},
			{"C", "G"},
			{"E", "F"},
			{"G", "F"},
			{"I", "H"},
			{"H", "G"},
			{"G", "J"},
			{"J", "K"},
			{"J", "L"},
			{"J", "M"}
	};

	auto result = schedule(constraints);

	Utils::printVec(result);

}

