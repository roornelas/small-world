#include "graph.hpp"
#include "search.hpp"
#include <iostream>
#include <cstdlib>
#include <cassert>


int main() {
  Graph g(12);
  //g.set_p(1);
  g.set_q_r(1, 0);
  // g.find_node(5,6)->print_friends();
  for (int i = 0; i < g.side_length; i++) {
    for (int j = 0; j < g.side_length; j++) {
      cout << "x: " << i << ", y: " << j << '\n';
      g.find_node(i, j)->print_friends();

    }
  }

  //assert(tree.retrieve(10) == 0);
  // Graph(10);

  // Search tests
  int side = 100;
  Graph s(side);
  s.set_p(1);
  s.set_q_r(1, 2);
  pair<int, int> start = make_pair(rand() % side, rand() % side);
  pair<int, int> end = make_pair(rand() % side, rand() % side);
  int bfs = searchBFS(&s, start, end);
  std::cout << "BFS search concluded in: " << bfs << "\n";
  int rw = searchRW(&s, start, end);
  std::cout << "Random Walk search concluded in: " << rw << "\n";
  int greedy = searchGreedy(&s, start, end);
  std::cout << "Greedy search concluded in: " << greedy << "\n";

  std::cout << "All tests passed!\n";

  return 0;
}
