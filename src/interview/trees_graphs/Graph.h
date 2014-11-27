/*
 * Graph.h
 *
 *  Created on: Nov 27, 2014
 *      Author: adam
 */

#ifndef INTERVIEW_TREES_GRAPHS_GRAPH_H_
#define INTERVIEW_TREES_GRAPHS_GRAPH_H_

#include <vector>

struct Edge : public std::pair<int, int> {

	Edge(int from, int to, float weight)
			: std::pair<int, int>(from, to), weight(weight) {}

	float weight;
};

class Vertex {
	int n;
public:
	Vertex(int n) : n(n) {}

	void addEdge(Edge edge) {
		if(edge.first == n) {
			outgoingEdges.push_back(edge);
		}
	}

	std::vector<Edge> outgoingEdges;
};



template<class Vertex = Vertex, class Edge = Edge>
class Graph : public std::vector<Vertex> {
public:
	Graph(int n) {
		this->reserve(n);
		for(int i = 0; i < n; ++i) {
			this->emplace_back(i);
		}
	}

	void addEdge(const Edge& edge) {
		this->at(edge.first).addEdge(edge);
		this->at(edge.second).addEdge(edge);
	}
};

struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	int data;

	TreeNode(int data, TreeNode* right = nullptr, TreeNode* left = nullptr, TreeNode* parent = nullptr)
	: data(data), right(right), left(left), parent(parent) {}

	void clear() {
		if(left) {
			left->clear();
		}

		if(right) {
			right->clear();
		}

		delete this;
	}
};

#endif /* INTERVIEW_TREES_GRAPHS_GRAPH_H_ */
