#include "graph.h"
#include <iostream>

int main()
{
	graph::Graph g2(8);

	g2.addEdgeList(0, 1); g2.addEdgeList(0, 2);
	g2.addEdgeList(1, 3);
	g2.addEdgeList(2, 1); g2.addEdgeList(2, 5);
	g2.addEdgeList(3, 4); g2.addEdgeList(3, 5);
	
	g2.addEdgeList(5, 1);
	g2.addEdgeList(6, 4); g2.addEdgeList(6, 7);
	g2.addEdgeList(7, 6);

	g2.DFS(0);    
	g2.printPredecessor();
	g2.printDiscover();
	g2.printFinish();

	std::cin.get();
	return 0;
}