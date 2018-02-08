#include "graph.h"
#include <iostream>

int main()
{
	graph::Graph g1(9);

	g1.addEdgeList(0, 1); g1.addEdgeList(0, 2); g1.addEdgeList(0, 3);
	g1.addEdgeList(1, 0); g1.addEdgeList(1, 4);
	g1.addEdgeList(2, 0); g1.addEdgeList(2, 4); g1.addEdgeList(2, 5); g1.addEdgeList(2, 6); g1.addEdgeList(2, 7);
	g1.addEdgeList(3, 0); g1.addEdgeList(3, 7);
	g1.addEdgeList(4, 1); g1.addEdgeList(4, 2); g1.addEdgeList(4, 5);
	g1.addEdgeList(5, 2); g1.addEdgeList(5, 4); g1.addEdgeList(5, 8);
	g1.addEdgeList(6, 2); g1.addEdgeList(6, 7); g1.addEdgeList(6, 8);
	g1.addEdgeList(7, 2); g1.addEdgeList(7, 3); g1.addEdgeList(7, 6);
	g1.addEdgeList(8, 5); g1.addEdgeList(8, 6);

	g1.BFS(0);
	g1.printDistance();
	g1.printPredecessor();

	std::cin.get();
	return 0;
}