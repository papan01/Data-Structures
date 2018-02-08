#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <list>
#include <queue>

namespace graph
{
	class Graph
	{
	public:
		Graph() : num_vertex_(0) {}
		Graph(const int& size) : num_vertex_(size)
		{
			adjacencyList_.resize(num_vertex_);
		}

		~Graph();

		void initialization();

		void addEdgeList(const int& from, const int& to);
		void BFS(const int& start); //Breadth-First Search
		void DFS(const int& start); //Depth-First Search
		void DFSVisit(const int& vertex, int &time);
		void connected_component_BFS(const int& vertex);
		void connected_component_DFS(const int& vertex);

		Graph graphTranspose();

		int getColor(const int& index) { return color_[index]; }
		int getFinish(const int& index) { return finish_[index]; }
		int getPredecessor(const int& index) { return predecessor_[index]; }

		void printDistance();
		void printPredecessor();
		void printDiscover();
		void printFinish();
		void printDataArray(int *array);
		void printSCCs(int start = 0);
		
		void TopologicalSort(int start = 0);
	private:
		enum 
		{
			WHITE,
			GRAY,
			BLACK
		};

		int num_vertex_;
		std::vector<std::list<int>> adjacencyList_;
		int *color_,
			*distance_,
			*predecessor_, // -1:no predecessor, express origin
			*discover_,
			*finish_;

		void setCollapsing(int current);
		void QuickSort(int *vec, int* index_order, int front, int end);
		int Partition(int *vec, int* index_order, int front, int end);
		void swap(int *x, int *y);
	};

}



#endif // !GRAPH_H

