#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <vector>

using namespace std;

enum color_t{BLACK = -1, GRAY = 0, WHITE = 1};

template <class T>
class Graph
{
	private:
		/* maps an int to a list of its neighbors */
		std::map<int, std::vector<int>> vertices;

		//data that is stored in the verticies
		vector<T> vertexData;

		vector<color_t> color;
		vector<int> distance;
		vector<int> parent;

		int numElements = 0;

		const bool isDirectd;
		std::map<int, std::vector<int>> transpose;

		int numCycles;
		vector<vector<int>> cycles;

		vector<vector<int>> subGraphs; // used if if DFS finds fully connected components

	public:
		vector<int> getTranspose();//stores the transpose of the graph so it doesn't have to be computed later

		Graph(bool);
		bool addVertex(int);

		bool addEdge(int,int); // add edge

		void print(); // prints the adjacency list of each vertex, to show the structure

		bool isDirected() const {return isDirectd;};
		bool isCyclic() const {return numCycles > 0;};
		bool isDAG() const {return isDirectd && numCycles == 0;};

		vector<int> Dfs(int);
		vector<int> Dfs(int, map<int, vector<int>>);
		vector<int> topoSort();

		vector<vector<int>> connectedComps();

};
#endif
