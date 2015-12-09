CXXFLAGS=-std=c++11 -g -fPIC

TARGETS = test_graph 

all: $(TARGETS)


test_graph: test_graph.o
	g++ -o test_graph test_graph.o $(CXXFLAGS)

gui: gui.cpp
	g++ `pkg-config --cflags --libs cairomm-1.0` -o gui gui.cpp -std=c++11 -g -fPIC


%.o: %.cpp %.hpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o $(TARGETS)
