/*
******searches.cpp*******
Library to search a graph for a path from starting point to an end point.
Depends on graph.hpp.
Assumes that a path exists between the two provided points.
*/

#pragma once

#include "graph.hpp"

#include <set>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>


// BFS Search
int searchBFS (Graph* g, pair<int, int> start, pair<int, int> end) {
  int i1 = start.first;
  int j1 = start.second;
  int i2 = end.first;
  int j2 = end.second;

  set<Node*> visited;
  queue<Node*> nodes;
  unordered_map<Node*, Node*> parents;
  Node* begin = g->find_node(i1, j1);
  Node* target = g->find_node(i2, j2);
  Node* curr = begin;
  visited.insert(curr);

  for (pair<int, int> f : curr->friends) {
    Node* temp = g->find_node(f.first, f.second);
    if (visited.find(temp) == visited.end()) {
      nodes.push(temp);
      parents.insert(make_pair(temp, curr));
    }
  }

  while (curr != target) {
    curr = nodes.front();
    nodes.pop();
    visited.insert(curr);

    for (pair<int, int> f : curr->friends) {
      Node* temp = g->find_node(f.first, f.second);
      if (visited.find(temp) == visited.end()) {
        nodes.push(temp);
        parents.insert(make_pair(temp, curr));
      }
    }
  }

  int dist = 0;
  curr = target;
  while (curr != begin) {
    dist++;
    curr = parents.at(curr);
  }
  return dist;
};

// Random Walk Search
int searchRW (Graph* g, pair<int, int> start, pair<int, int> end) {
  int i1 = start.first;
  int j1 = start.second;
  int i2 = end.first;
  int j2 = end.second;

  int length = 0;

  Node* curr = g->find_node(i1, j1);
  Node* target = g->find_node(i2, j2);

  while (curr != target) {
    length++;
    int r = rand() % curr->friends.size();
    set<pair<int, int>>::iterator it(curr->friends.begin());
    advance(it, r);
    curr = g->find_node(*it);
  }
  return length;
};

// Greedy Search
int searchGreedy (Graph* g, pair<int, int> start, pair<int, int> end) {
  int i1 = start.first;
  int j1 = start.second;
  int i2 = end.first;
  int j2 = end.second;

  int length = 0;

  Node* curr = g->find_node(i1, j1);
  Node* target = g->find_node(i2, j2);

  while (curr != target) {
    length++;
    int mindist = std::numeric_limits<int>::max();
    Node* temp;
    for (pair<int, int> f : curr->friends) {
      int tempdist = Graph::lattice_distance(f, end);
      if (tempdist < mindist) {
        mindist = tempdist;
        temp = g->find_node(f.first, f.second);
      }
    }
    curr = temp;
  }
  return length;
};
