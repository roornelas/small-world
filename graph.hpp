/** This is the initial code we have written to analyze the algorithms and model presented in the research
 * paper: The Small-World Phenomenon: An Algorithmic Perspective by Jon Kleinberg.
 * We made some design decisions about our graph to model acquaintances between people, including funtional
 * randomization to model long-range friendships. We ran a couple of tests and verified that our graph is
 * behaving as expected for different parameters p,q, and r.
 * (Code is still messy and uncommented, will clean it soon :)
 */


#pragma once

#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include <cmath>
#include <algorithm>

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
};

class Graph {
public:
	int side_length;
	int r;
	vector<vector<Node*>> matrix;

	Graph(int side_length): side_length(side_length) {
		matrix.resize(side_length, vector<Node*>(side_length, nullptr ));
		for (int i = 0; i < side_length; i++) {
			for (int j = 0; j < side_length; j++) {
				//cout << "x: "<< i << ", y: "<< j << '\n';
				//matrix[i][j] = Node::alloc_node(i, j);
				matrix[i][j] = new Node(i, j);

				//cout << "x: " << matrix[i][j]->coors.first << ", y: " << matrix[i][j]->coors.second << '\n';
			}
		}
	}

	~Graph() {
		for (int i = 0; i < side_length; i++) {
			for (int j = 0; j < side_length; j++) {
				if (matrix[i][j]) {
					delete(matrix[i][j]);
				}
			}
		}
	}

	void set_p(int p) {
		for (int i = 0; i < side_length; i++) {
			for (int j = 0; j < side_length; j++) {
				for (int k = -p; k <= p; k++) {
					for (int l = -p; l <= p; l++) {
						if (abs(k) + abs(l) <= p && i + k >= 0 && i + k < side_length && j + l >= 0 && j + l < side_length && (k != 0 || l != 0)) {
							add_edge(make_pair(make_pair(i, j), make_pair(i + k, j + l)));
						}
					}
				}
			}
		}
	}

	int static lattice_distance(pair<int, int> u, pair<int, int> v) {
		return abs(v.first - u.first) + abs(v.second - u.second);
	}

	double add_long_edges(pair<int, int> vertex, int q, int r) {

		//cout << "Adding long edges of " << "(" << vertex.first << ", " << vertex.second << ") \n ";
		double norm_const = 0;
		int vertex_index = vertex.first * side_length + vertex.second;
		vector<double> cdf;

		cdf.resize(side_length * side_length);

		for (int i = 0; i < side_length; i++) {
			for (int j = 0; j < side_length; j++) {
				if (!(vertex.first == i && vertex.second == j)) {
					norm_const +=  pow(lattice_distance(vertex, make_pair(i, j)), -r);
				}
			}
		}

		double total = 0;


		for (int i = 0; i < side_length * side_length; i++) {
			double diff = (i == vertex_index) ? 0 : pow(lattice_distance(vertex, make_pair(i / side_length, i % side_length)), -r) / norm_const;
			total += diff;
			cdf[i] = total;

			//cout << "Total " << i / side_length << ", " << i % side_length << " : " << total << ", diff: " << diff << ", norm_const = " << norm_const << ", cdf: " << cdf[i] << '\n';
		}

		for (int i = 0; i < q; i++) {
			double random = ((double) rand() / (RAND_MAX));
			vector<double>::iterator low = std::upper_bound(cdf.begin(), cdf.end(), random);
			int cdf_index = distance(cdf.begin(), low);
			//cout << "Random " << random << ", cdf_index: " << cdf_index << ", max distance: " << distance(cdf.begin(), cdf.end()) << '\n';

			pair<int, int> neighbor = make_pair(cdf_index / side_length, cdf_index % side_length);

			add_edge(make_pair(vertex, neighbor));
		}
	}

	void set_q_r(int q, int r) {
		srand(time(NULL));
		for (int i = 0; i < side_length; i++) {
			for (int j = 0; j < side_length; j++) {
				add_long_edges(make_pair(i, j), q, r);
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
			add_edge(edge);
		}
		return;
	}

	void add_edge(pair<pair<int, int>, pair<int, int>> edge) {
		find_node(edge.first)->add_edge(edge.second);
		return;
	}

private:
};

