/*
 * test.cpp
 *
 *  Created on: May 28, 2014
 *      Author: Adam Kosiorek
 */


#include "gtest/gtest.h"
#include "Utils.h"
#include "Graph.h"
#include <queue>
#include <limits>

struct ByDFS {
	const Graph<>& g;
	std::vector<bool> visited;

	ByDFS(const Graph<>& g) : g(g), visited(g.size(), false) {}

	bool isPathBetween(int from, int to) {
		if(from == to) {
			return true;
		}

		visited[from] = true;
		const Vertex& v = g[from];
		for(const Edge& e : v.outgoingEdges) {
			if(!visited[e.second]) {
				if(isPathBetween(e.second, to)) {
					return true;
				}
			}
		}
		return false;
	}
};

struct ByBFS {
	const Graph<>& g;
	std::vector<bool> visited;
	std::queue<int> toVisit;

	ByBFS(const Graph<>& g) : g(g), visited(g.size(), false) {}

	bool isPathBetween(int from, int to) {

		toVisit.push(from);
		while(!toVisit.empty()) {

			int current = toVisit.front();
			toVisit.pop();
			if(current == to) {
				return true;
			}
			if(!visited[current]) {
				visited[current] = true;
				for(const auto& e : g[current].outgoingEdges) {
					toVisit.push(e.second);
				}
			}
		}
		return false;
	}
};

struct ByDijkstra {
	const Graph<>& g;
	std::vector<float> cost;
	std::vector<int> prev;
	std::vector<bool> visited;

	struct EdgeComparator {

		bool operator() (const Edge* e1, const Edge* e2) const {
			return e1->weight > e2->weight;
		}
	};

//	std::priority_queue<const Edge*> edgeQueue;
	std::priority_queue<const Edge*, std::vector<const Edge*>, EdgeComparator> edgeQueue;

	ByDijkstra(const Graph<>& g) : g(g), cost(g.size(), std::numeric_limits<float>::max()), prev(g.size()), visited(g.size(), false) {}

	void addEdges(int v) {
		for(const auto& e : g[v].outgoingEdges) {
			edgeQueue.push(&e);
		}
	}

	bool isPathBetween(int from, int to) {
		prev[from] = from;
		cost[from] = 0;
		visited[from] = true;
		addEdges(from);

		while(!edgeQueue.empty()) {
			const Edge* e = edgeQueue.top();
			edgeQueue.pop();

			if(!visited[e->second]) {
				visited[e->second] = true;
				addEdges(e->second);
			}

			float newCost = cost[e->first] + e->weight;
			if(newCost < cost[e->second]) {
				cost[e->second] = newCost;
				prev[e->second] = e->first;
			}
		}
		Utils::printVec(cost);
		return cost[to] != std::numeric_limits<float>::max();
	}
};

struct ByAStar {
	const Graph<>& g;
	std::vector<bool> visited;

	ByAStar(const Graph<>& g) : g(g), visited(g.size(), false) {}

	bool isPathBetween(int from, int to) {

	}
};

struct IsPathBetweenTest : public testing::Test {

	IsPathBetweenTest() : withPath(5), withoutPath(5) {

		withPath.addEdge(Edge(0, 1, 1));
		withPath.addEdge(Edge(1, 2, 2));
		withPath.addEdge(Edge(2, 3, 3));
		withPath.addEdge(Edge(3, 0, 4));
		withPath.addEdge(Edge(1, 4, 6));
		withPath.addEdge(Edge(4, 2, 5));

		withoutPath.addEdge(Edge(0, 1, 1));
		withoutPath.addEdge(Edge(1, 2, 2));
		withoutPath.addEdge(Edge(2, 3, 3));
		withoutPath.addEdge(Edge(3, 0, 4));
	}

	Graph<> withPath;
	Graph<> withoutPath;
};


TEST_F(IsPathBetweenTest, DFSTest) {

	ASSERT_TRUE(ByDFS(withPath).isPathBetween(0, 4));
	ASSERT_FALSE(ByDFS(withoutPath).isPathBetween(0, 4));
}

TEST_F(IsPathBetweenTest, BFSTest) {

	ASSERT_TRUE(ByBFS(withPath).isPathBetween(0, 4));
	ASSERT_FALSE(ByBFS(withoutPath).isPathBetween(0, 4));
}

TEST_F(IsPathBetweenTest, DijkstraTest) {

	ASSERT_TRUE(ByDijkstra(withPath).isPathBetween(0, 4));
	ASSERT_FALSE(ByDijkstra(withoutPath).isPathBetween(0, 4));
}
