#include "MST.h"


int main()
{
	graph::GraphMST g6(7);
	g6.addEdgeMatrix(0, 1, 5); g6.addEdgeMatrix(0, 5, 3);
	g6.addEdgeMatrix(1, 0, 5); g6.addEdgeMatrix(1, 2, 10); g6.addEdgeMatrix(1, 4, 1); g6.addEdgeMatrix(1, 6, 4);
	g6.addEdgeMatrix(2, 1, 10); g6.addEdgeMatrix(2, 3, 5); g6.addEdgeMatrix(2, 6, 8);
	g6.addEdgeMatrix(3, 2, 5); g6.addEdgeMatrix(3, 4, 7); g6.addEdgeMatrix(3, 6, 9);
	g6.addEdgeMatrix(4, 1, 1); g6.addEdgeMatrix(4, 3, 7); g6.addEdgeMatrix(4, 5, 6); g6.addEdgeMatrix(4, 6, 2);
	g6.addEdgeMatrix(5, 0, 3); g6.addEdgeMatrix(5, 4, 6);
	g6.addEdgeMatrix(6, 1, 4); g6.addEdgeMatrix(6, 2, 8); g6.addEdgeMatrix(6, 3, 9); g6.addEdgeMatrix(6, 4, 2);

	std::cout << "MST found by Kruskal:" << std::endl;
	g6.KruskalMST();

	std::cout << "MST found by Prim:" << std::endl;
	g6.PrimMST(2);

	std::cin.get();
	return 0;
}