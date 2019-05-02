#include "Graph.h"

template <class T>
Graph<T>::Graph(bool isDir)
	:isDirectd(isDir)//not a typo, const var is misspelled so the getter function has the right spelling
{

}
	template <class T>
bool Graph<T>::addVertex(int v)
{
	if(v != numElements +1)
		cout << "add vertices in order" << endl;
	else
	{
		//try to insert a vector of ints at
		pair<map<int, vector<int>>::iterator, bool> ret;
		ret = vertices.insert(pair<int, vector<int>>(v, vector<int>()));

		if(ret.second == false)
			cout << v << " already in graph" << endl;
		else
			numElements++;

		return ret.second;
	}
}

	template <class T>
bool Graph<T>::addEdge(int from, int to)
{
	//find the two vertecies in the graph
	map<int, vector<int>>::iterator fromIter = vertices.find(from);
	map<int, vector<int>>::iterator toIter = vertices.find(to);

	if(fromIter != vertices.end() && toIter != vertices.end())//if the 2 vertexes are in the graph
	{
		//make sure the edge vectors are big enough
		if(to > vertices[from].max_size())
			vertices[from].resize(to);
		if(isDirectd)
			transpose[to].resize(from);
		else if(from > vertices[to].max_size())
			vertices[to].resize(from);

		//add the nodes to each other's edge list
		vertices[from].push_back(to);
		if(isDirectd)//if it's directed, add the reverse edge to the transpose
			transpose[to].push_back(from);
		else//if it's undirected, add the symmetrical edge
			vertices[to].push_back(from);

		return true;
	}
	return false;//if the node wasn't added
}
template <class T>
//print out adjacency list
void Graph<T>::print(){
  for (auto i = vertices.begin(); i !=vertices.end(); i++)
  {
    cout<<"nodes "<<i->first<<endl;
  }
}
	template <class T>
vector<int> Graph<T>::Dfs(int start)
{
	return Dfs(start, vertices);
}
	template <class T>
vector<int> Graph<T>::Dfs(int start, map<int, vector<int>> adj)
{
	vector<int> topoSort;
	map<int, vector<int>>::iterator sIt = adj.begin();

	cout << "#" << numElements << endl;
	color = vector<color_t>(numElements + 1, WHITE);//adj.size(), WHITE);
	distance = vector<int>(numElements + 1, -1);//adj.size(), -1);
	parent = vector<int>(numElements + 1, -1);//adj.size(), -1);
	stack<int> neighbors = stack<int>();
	numCycles = 0;
	int time = 0;
	int current = start;
	while(sIt != adj.end())
	{
		if(color[sIt->first] != BLACK)//if the vertex was already discovered
		{
			current = sIt->first;
			int u = current;

			if(color[parent[u]] == WHITE)//there is a new subgraph
			{
				cout << "new sub-graph " << sIt->first;
				vector<vector<int>>::iterator subGraphsIter = subGraphs.begin();
				subGraphs.insert(subGraphsIter, topoSort);
				topoSort.clear();
			}
		//	else//add node to current subgraph

				if(color[current] == WHITE)
				{
					color[current] = GRAY;
					if(distance[current])
						distance[current] = 0;
					neighbors.push(current);
				}
			int numNeighbors = adj[u].size();

			while(!neighbors.empty())
			{
				u = neighbors.top();
				neighbors.pop();
				cout << "stack pop " << u << " dist " << distance[u] << " at time " << time++ << endl;
				for(int v : adj[u])
				{
					cout << "neighbor: " << v << endl;

					if(color[v] == WHITE)
					{
						color[v] = GRAY;
						distance[v] = distance[u] + 1;
						parent[v] = u;
						neighbors.push(v);
					}
					else if(color[v] == GRAY)
					{
						cout << " There's a cycle" << endl;
						numCycles++;
					}
				}
			}
			cout << "time: " << time << " finished " << u << endl;
			if(color[u] != BLACK)
			{
				color[u] = BLACK;
				topoSort.insert(topoSort.begin(), u);
			}
		}	sIt++;
	}
	for(int i = 0; i < distance.size(); i++)
	{
		if(distance[i] != -1)
			cout <<  "Distance to " << i << " is " << distance[i] << endl;
	}
	return topoSort;
}

	template <class T>
vector<int> Graph<T>::topoSort()
{
	vector<int> output;
	map<int, vector<int>>::iterator it = vertices.begin();
	if(isDAG() || numCycles < 0)
	{
		output = Dfs(it->first);
	}else
	{
		cout << "The graph is not a DAG." << endl;
	}
	for(int i : output)
		cout << i << " ";
	cout << endl;
	return output;
}
	template <class T>
vector<vector<int>> Graph<T>::connectedComps()
{
	if(!isDAG() || numCycles < 0)
	{
		if(isDirected())
			Dfs(0);
	}
	vector<int> output = Dfs(1, transpose);

	return subGraphs;
}

	template <class T>
vector<int> Graph<T>::getTranspose()
{
	vector<int> t;
	vector<int>::reverse_iterator rit = parent.rbegin();
	for(; rit != parent.rend(); ++rit )
		t.push_back(*rit);
	return t;
}
