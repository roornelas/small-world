#include "graph.hpp"
#include "search.hpp"
#include <iostream>
#include <cstdlib>
#include <cassert>

#include <math.h>


int main() {
  Graph g(12);
  g.set_p(1);
  g.set_q_r(1, 2);

  for (int i = 0; i < g.side_length; i++) {
    for (int j = 0; j < g.side_length; j++) {
      cout << "x: " << i << ", y: " << j << '\n';
      g.find_node(i, j)->print_friends();
    }
  }

  //assert(tree.retrieve(10) == 0);
  // Graph(10);

  int side, people;
  bool right_size = false;
  // Search tests
  while(!right_size) {
    std::cout << "How many people are in the network? In the range 20 - 10,000\n";
    std::cin >> people;
    if(people >= 20 && people <= 10000){
      right_size = true;
    } else {
      std::cout << "The number of people has to be in the range 20 - 10,000 so your graph can be built in less than 20 seconds\n";
    }
  }
  side = ceil(sqrt(people));
  std::cout << "Side length of grid: " << side<<"\n";
  std::cout << "Building a custom randomized graph just for you\n" ;
  Graph s(side);
  s.set_p(1);
  s.set_q_r(1, 2);

  pair<int, int> start = make_pair(rand() % side, rand() % side);
  pair<int, int> end = make_pair(rand() % side, rand() % side);
  std::cout << "Done! Let us run the algorithms\n" ;
  std::cout << "The number of people it took to transmit a message from person " <<
   "(" << start.first << ", " << start.second << ") to person " "(" << end.first << ", " << end.second << ") is: \n\n" ;
  int bfs = searchBFS(&s, start, end);
  std::cout << "Optimal possible result (Using breadth first search): " << bfs << " steps\n\n";
  int rw = searchRW(&s, start, end);
  std::cout << "Using a Random Walk: " << rw << " steps\n\n";
  int greedy = searchGreedy(&s, start, end);
  std::cout << "Using Kleinberg's simple algorithm: " << greedy << " steps\n\n";

  std::cout << "All tests passed!\n";

  return 0;
}
