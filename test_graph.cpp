#include "graph.hpp"

#include <iostream>
#include <cstdlib>
#include <cassert>



int main() {
  Graph g(12);
  //g.set_p(1);
  g.set_q_r(1,0);
// g.find_node(5,6)->print_friends();
  for (int i = 0; i < g.side_length; i++) {
    for (int j = 0; j < g.side_length; j++) {
      cout << "x: " << i << ", y: " << j << '\n';
      g.find_node(i, j)->print_friends();

    }
  }

  //assert(tree.retrieve(10) == 0);
// Graph(10);
  std::cout << "All tests passed!\n";
   std::cout << "Lattice distance\n"<< Graph::lattice_distance(make_pair(6,7), make_pair(6,7));

  return 0;
}
