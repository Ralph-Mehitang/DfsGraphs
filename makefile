all: graph clean

graph: instantiation.cpp Graph.o Main.o
	g++ -std=c++11 instantiation.cpp -o graph -g

Graph.o: Graph.cpp Graph.h
	g++ -std=c++11 -c Graph.cpp -g

Main.o: Main.cpp Graph.h
	g++ -std=c++11 -c Main.cpp -g

clean:
	rm -rf *o
