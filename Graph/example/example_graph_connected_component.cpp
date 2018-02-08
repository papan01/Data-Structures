#include "graph.h"
#include <iostream>

int main()
{
	graph::Graph g3(9);

	g3.addEdgeList(0, 1);
	g3.addEdgeList(1, 0); g3.addEdgeList(1, 4); g3.addEdgeList(1, 5);
	
	g3.addEdgeList(3, 6);
	g3.addEdgeList(4, 1); g3.addEdgeList(4, 5);
	g3.addEdgeList(5, 1); g3.addEdgeList(5, 4); g3.addEdgeList(5, 7);
	g3.addEdgeList(6, 3); g3.addEdgeList(6, 8);
	g3.addEdgeList(7, 5);
	g3.addEdgeList(8, 6);

	g3.connected_component_DFS(0);
	std::cout << std::endl;
	g3.connected_component_BFS(0);
	std::cout << std::endl;

	std::cin.get();
	return 0;
}