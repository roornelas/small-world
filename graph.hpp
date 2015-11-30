#pragma once

#include <utility>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

class Node {
public:
	pair<int, int> coors;
	set<pair<int, int>> friends;
	Node(int x, int y): coors(make_pair(x, y)) {}
	Node() : coors(make_pair(-1, -1)) {}
	void update_coors(int x, int y) {
		coors = make_pair(x, y);
	}
	void add_edge(pair<int, int> v) {
		friends.insert(v);
	}
	void print_friends() {
		cout << "Friends of " << "(" << this->coors.first << ", " << this->coors.second << "): ";
		for (pair<int, int> f : this->friends) {
			cout << "(" << f.first << ", " << f.second << "), ";
		}
		cout << "\n";
		return;
	}
	static Node* alloc_node(int x, int y) {
		Node* new_node = (Node*)malloc(sizeof(Node));
		*new_node = Node(x, y);
		return new_node;
	}
};
class Graph {
public:
	int side_length;
	vector<vector<Node*>> matrix;
	Graph(int side_length): side_length(side_length) {
		matrix.resize(side_length, vector<Node*>(side_length, nullptr ));
		for (int i = 0; i < side_length; i++) {
			for (int j = 0; j < side_length; j++) {
				//cout << "x: "<< i << ", y: "<< j << '\n';
				matrix[i][j] = Node::alloc_node(i, j);

				cout << "x: " << matrix[i][j]->coors.first << ", y: " << matrix[i][j]->coors.second << '\n';
			}
		}
	}
	Node* find_node(int i, int j) {
		return matrix[i][j];
	}
	Node* find_node(pair<int, int> v) {
		return find_node(v.first, v.second);
	}
	void add_edges(set<pair<pair<int, int>, pair<int, int>>> edges) {
		for (pair<pair<int, int>, pair<int, int>> edge : edges) {
			/*if(edge.first >= this->side_length || edge.first < 0 || edge.second >=this->side_length || edge.second < 0){
				cout << "Error \n";
				return;
			}*/
			add_edge(edge);
		}
		return;
	}
	void add_edge(pair<pair<int, int>, pair<int, int>> edge) {
		find_node(edge.first)->add_edge(edge.second);
		find_node(edge.second)->add_edge(edge.first);
		return;
	}

private:
};

