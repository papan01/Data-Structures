#include "MST.h"

graph::GraphMST::~GraphMST()
{
}

void graph::GraphMST::addEdgeMatrix(const int & from, const int & to, const int & weight)
{
	adjacencyMatrix_[from][to] = weight;
}

void graph::GraphMST::KruskalMST()
{
	Edge* edgeSetMST = new Edge[num_vertex_];

	int edge_count = 0;
	int* subSet = new int[num_vertex_];
	std::fill_n(subSet, num_vertex_, -1);
	
	std::vector<Edge> increaseWeight;
	sortedEdgeWeight(increaseWeight);

	for (unsigned int i = 0 ; i < increaseWeight.size() ; i++)
	{
		if (setCollapsing(subSet, increaseWeight[i].from) != setCollapsing(subSet, increaseWeight[i].to)) {
			edgeSetMST[edge_count++] = increaseWeight[i];
			unionSet(subSet, increaseWeight[i].from, increaseWeight[i].to);
		}
	}

	std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2" << " : weight\n";
	for (int i = 0; i < num_vertex_ - 1; i++) {
		std::cout << std::setw(3) << edgeSetMST[i].from << " - " << std::setw(3) << edgeSetMST[i].to
			<< " : " << std::setw(4) << edgeSetMST[i].weight << "\n";
	}

	delete[] edgeSetMST;
	delete[] subSet;
}

void graph::GraphMST::PrimMST(const int& start)
{
	int* key = new int[num_vertex_];
	int* predecessor = new int[num_vertex_] {-1};
	bool* visited = new bool[num_vertex_] {false};

	std::fill_n(key, num_vertex_, INT_MAX);
	std::fill_n(predecessor, num_vertex_, -1);
	std::fill_n(visited, num_vertex_, false);

	key[start] = 0;
	for (int i = 0; i < num_vertex_; i++) {
		int u = extractMinKey(key, visited);
		visited[u] = true;
		for (int i = 0; i < num_vertex_; i++) {
			if (visited[i] == false && adjacencyMatrix_[u][i] != 0 && adjacencyMatrix_[u][i]<key[i]) {
				predecessor[i] = u;
				key[i] = adjacencyMatrix_[u][i];
			}
		}
	}

	std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2" << " : weight\n";
	int i = (start + 1) % num_vertex_;
	while (i != start) {
		std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
			<< " : " << std::setw(4) << adjacencyMatrix_[predecessor[i]][i] << "\n";
		i = (++i) % num_vertex_;       
	}

	delete[] visited;
	delete[] predecessor;
	delete[] key;
}

int graph::GraphMST::extractMinKey(int * key, bool * visited)
{
	int min = INT_MAX, min_idx = 0;
	for (int i = 0; i < num_vertex_; i++) {
		if (visited[i] == false && key[i] < min) {
			min = key[i];
			min_idx = i;
		}
	}
	return min_idx;
}

void graph::GraphMST::sortedEdgeWeight(std::vector<Edge>& vec)
{
	for (int i = 0; i < num_vertex_ - 1; i++) {
		for (int j = i + 1; j < num_vertex_; j++) {
			if (adjacencyMatrix_[i][j] != 0) {
				vec.push_back(Edge(i, j, adjacencyMatrix_[i][j]));
			}
		}
	}
	std::sort(vec.begin(), vec.end(), [](const Edge& a, const Edge& b) {return a.weight < b.weight; });
}

int graph::GraphMST::setCollapsing(int * subset, int i)
{
	int root;  // root
	for (root = i; subset[root] >= 0; root = subset[root]);

	while (i != root) {
		int parent = subset[i];
		subset[i] = root;
		i = parent;
	}

	return root;
}

void graph::GraphMST::unionSet(int * subset, int x, int y)
{
	int xroot = setCollapsing(subset, x),
		yroot = setCollapsing(subset, y);

	if (subset[xroot] <= subset[yroot]) {     
		subset[xroot] += subset[yroot];
		subset[yroot] = xroot;
	}
	else {    
		subset[yroot] += subset[xroot];
		subset[xroot] = yroot;
	}
}
