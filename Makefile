CXXFLAGS=-std=c++11 -g -fPIC

TARGETS = test_graph 

all: $(TARGETS)


test_graph: test_graph.o
	g++ -o test_graph test_graph.o $(CXXFLAGS)

%.o: %.cpp graph.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o $(TARGETS)
