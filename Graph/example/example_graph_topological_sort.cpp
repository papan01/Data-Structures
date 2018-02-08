#include "graph.h"
#include <iostream>

int main()
{
	graph::Graph g5(15);            // 建立如圖二(a)的DAG
	g5.addEdgeList(0, 2);
	g5.addEdgeList(1, 2);
	g5.addEdgeList(2, 6); g5.addEdgeList(2, 7);
	g5.addEdgeList(3, 4);
	g5.addEdgeList(4, 5);
	g5.addEdgeList(5, 6); g5.addEdgeList(5, 14);
	g5.addEdgeList(6, 8); g5.addEdgeList(6, 9); g5.addEdgeList(6, 11); g5.addEdgeList(6, 12);
	g5.addEdgeList(7, 8);
	g5.addEdgeList(9, 10);
	g5.addEdgeList(12, 13);

	g5.TopologicalSort();
	g5.TopologicalSort(4);

	std::cin.get();
	return 0;
}