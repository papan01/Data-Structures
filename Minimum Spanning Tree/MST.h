#ifndef MST_H
#define MST_H
#include <iostream>
#include <vector>
#include <list>
#include <iomanip> 
#include <algorithm>


namespace graph
{
	class Edge
	{
	public:
		int from, to, weight;
		Edge() : from(0), to(0), weight(0) {}
		Edge(const int& from_, const int& to_, const int& weight_) : from(from_), to(to_), weight(weight_) {}
	};

	class GraphMST
	{
	public:
		GraphMST() : num_vertex_(0) {}
		GraphMST(const int size) : num_vertex_(size)
		{
			adjacencyMatrix_.resize(num_vertex_);
			for (auto i = 0 ; i < num_vertex_ ; i++)
			{
				adjacencyMatrix_[i].resize(num_vertex_);
			}
		}
		
		~GraphMST();

		void addEdgeMatrix(const int& from, const int& to, const int& weight);

		//Kruskal's algorithm
		void KruskalMST();

		//Prim's algorithm
		void PrimMST(const int& start);
	private:
		int num_vertex_;
		std::vector<std::vector<int>> adjacencyMatrix_;

		void sortedEdgeWeight(std::vector<Edge> &vec);
		int setCollapsing(int *subset, int i);
		void unionSet(int *subset, int x, int y);

		int extractMinKey(int *key, bool *visited);
	};
}

#endif // !MST_H

