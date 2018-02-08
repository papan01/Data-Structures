#include "graph.h"
#include <iostream>

int main()
{
	graph::Graph g4(9);
	g4.addEdgeList(0, 1);
	g4.addEdgeList(1, 2); g4.addEdgeList(1, 4);
	g4.addEdgeList(2, 0); g4.addEdgeList(2, 3); g4.addEdgeList(2, 5);
	g4.addEdgeList(3, 2);
	g4.addEdgeList(4, 5); g4.addEdgeList(4, 6);
	g4.addEdgeList(5, 4); g4.addEdgeList(5, 6); g4.addEdgeList(5, 7);
	g4.addEdgeList(6, 7);
	g4.addEdgeList(7, 8);
	g4.addEdgeList(8, 6);

	std::cout << "Vertex(0) as starting point for the First DFS():\n\n";
	g4.printSCCs(0);
	std::cout << "Vertex(3) as starting point for the First DFS():\n\n";
	g4.printSCCs(3);

	std::cin.get();
	return 0;
}