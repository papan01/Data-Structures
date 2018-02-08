#include "graph.h"
#include <iomanip>
#include <iostream>
#include <algorithm>

graph::Graph::~Graph()
{
	delete color_;
	delete distance_;
	delete predecessor_;
	delete finish_;
	delete discover_;
}

void graph::Graph::initialization()
{
	color_ = new int[num_vertex_] { WHITE };
	discover_ = new int[num_vertex_]();
	finish_ = new int[num_vertex_]();
	predecessor_ = new int[num_vertex_];
	std::fill_n(predecessor_, num_vertex_, -1);
}

void graph::Graph::addEdgeList(const int & from, const int & to)
{
	adjacencyList_[from].push_back(to);
}

void graph::Graph::BFS(const int & start)
{
	color_ = new int[num_vertex_] {WHITE};
	distance_ = new int[num_vertex_] {-1};
	predecessor_ = new int[num_vertex_] {num_vertex_+1};

	std::queue<int> q;
	auto i = start;

	for (auto j = 0; j < num_vertex_; j++)
	{
		if (color_[i] == WHITE)
		{
			color_[i] = GRAY;
			distance_[i] = 0;
			predecessor_[i] = -1;
			q.push(i);
			while (!q.empty())
			{
				auto u = q.front();
				for (std::list<int>::iterator itr = adjacencyList_[u].begin();
					itr != adjacencyList_[u].end(); itr++)
				{
					if (color_[*itr] == WHITE)
					{
						color_[*itr] = GRAY;
						distance_[*itr] = distance_[u] + 1;
						predecessor_[*itr] = u;
						q.push(*itr);
					}
				}
				color_[u] = BLACK;
				q.pop();
			}
		}
		i = j;
	}

}

void graph::Graph::DFS(const int & start)
{
	initialization();

	int time = 0;
	auto i = start;
	for (auto j = 0; j < num_vertex_; j++)
	{
		if (color_[i] == WHITE)
			DFSVisit(i, time);
		i = j;
	}

}

void graph::Graph::DFSVisit(const int & vertex, int & time)
{
	color_[vertex] = GRAY;
	discover_[vertex] = ++time;
	for (std::list<int>::iterator itr = adjacencyList_[vertex].begin();
		itr != adjacencyList_[vertex].end(); itr++)
	{
		if (color_[*itr] == WHITE)
		{
			predecessor_[*itr] = vertex;
			DFSVisit(*itr, time);
		}
	}
	color_[vertex] = BLACK;
	finish_[vertex] = ++time;

}

void graph::Graph::connected_component_BFS(const int & vertex)
{
	BFS(vertex);
	printPredecessor();
	for (auto i = 0; i < num_vertex_; i++)
	{
		setCollapsing(i);
	}
	printPredecessor();
	int num_connected_component = 0;

	for (auto i = 0; i < num_vertex_; i++)
	{
		if (predecessor_[i] < 0)
		{
			std::cout << "Component#" << ++num_connected_component << ":" << i << " ";
			for (int j = 0; j < num_vertex_; j++) {
				if (predecessor_[j] == i) {
					std::cout << j << " ";
				}
			}
			std::cout << std::endl;
		}
	}
}

void graph::Graph::connected_component_DFS(const int & vertex)
{
	DFS(vertex);
	printPredecessor();
	for (auto i = 0; i < num_vertex_; i++)
	{
		setCollapsing(i);
	}
	printPredecessor();
	int num_connected_component = 0;

	for (auto i = 0; i < num_vertex_ ; i++)
	{
		if (predecessor_[i] < 0)
		{
			std::cout << "Component#" << ++num_connected_component << ":" << i << " ";
			for (int j = 0; j < num_vertex_; j++) {
				if (predecessor_[j] == i) {
					std::cout << j << " ";
				}
			}
			std::cout << std::endl;
		}
	}
}

graph::Graph graph::Graph::graphTranspose()
{
	Graph g(num_vertex_);
	for (auto i = 0; i < num_vertex_; i++)
	{
		for (auto itr = adjacencyList_[i].begin(); itr != adjacencyList_[i].end(); itr++)
		{
			g.addEdgeList(*itr, i);
		}
	}

	return g;
}

void graph::Graph::printDistance()
{
	std::cout << "Distance Array:" << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << i;
	}
	std::cout << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << distance_[i];
	}
	std::cout << std::endl;
}

void graph::Graph::printPredecessor()
{
	std::cout << "Predecessor Array:" << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << i;
	}
	std::cout << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << predecessor_[i];
	}
	std::cout << std::endl;

}

void graph::Graph::printDiscover()
{
	std::cout << "Discover Array:" << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << i;
	}
	std::cout << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << discover_[i];
	}
	std::cout << std::endl;
}

void graph::Graph::printFinish()
{
	std::cout << "Finish Array:" << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << i;
	}
	std::cout << std::endl;
	for (auto i = 0; i < num_vertex_; i++)
	{
		std::cout << std::setw(3) << finish_[i];
	}
	std::cout << std::endl;
}

void graph::Graph::printDataArray(int * array)
{
	for (int i = 0; i < num_vertex_; i++)
		std::cout << std::setw(4) << i;
	std::cout << std::endl;
	for (int i = 0; i < num_vertex_; i++)
		std::cout << std::setw(4) << array[i];
	std::cout << std::endl;
}

void graph::Graph::setCollapsing(int current)
{
	int root;  // root
	for (root = current; predecessor_[root] >= 0; root = predecessor_[root]);

	while (current != root) {
		int parent = predecessor_[current];
		predecessor_[current] = root;
		current = parent;
	}
}

void graph::Graph::QuickSort(int * vec, int* index_order, int front, int end)
{
	if (front < end) {
		int pivot = Partition(vec, index_order, front, end);
		QuickSort(vec, index_order, front, pivot - 1);
		QuickSort(vec, index_order, pivot + 1, end);
	}
}

int graph::Graph::Partition(int * vec, int* index_order, int front, int end)
{
	int pivot = vec[end];
	int i = front - 1;
	for (int j = front; j < end; j++) {
		if (vec[j] > pivot) {
			i++;
			swap(&vec[i], &vec[j]);
			swap(&index_order[i], &index_order[j]);
		}
	}
	swap(&vec[i + 1], &vec[end]);
	swap(&index_order[i + 1], &index_order[end]);
	i++;
	return i;   
}

void graph::Graph::swap(int * x, int * y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void graph::Graph::printSCCs(int start)
{
	DFS(start);

	std::cout << "First DFS() on Graph, finish time:" << std::endl;
	printFinish();

	Graph gTranspose(num_vertex_);
	
	gTranspose = graphTranspose();

	int* finishLargetoSmall = new int[num_vertex_];
	for (auto i = 0; i < num_vertex_; i++) {
		finishLargetoSmall[i] = i;
	}

	QuickSort(finish_, finishLargetoSmall, 0, num_vertex_ - 1);
	std::cout << "finish time order the numbers from greatest to least:" << std::endl;
	printDataArray(finishLargetoSmall);

	gTranspose.initialization();
	int time = 0;
	for (auto i = 0; i < num_vertex_; i++) {
		if (gTranspose.getColor(finishLargetoSmall[i]) == 0) {
			gTranspose.DFSVisit(finishLargetoSmall[i], time);
		}
	}

	std::cout << "Second DFS() on transpose graph, finish time:" << std::endl;
	gTranspose.printFinish();
	std::cout << "predecessor[] before SetCollapsing:\n";
	gTranspose.printPredecessor();

	for (int i = 0; i< num_vertex_; i++)
		gTranspose.setCollapsing(i);

	std::cout << "predecessor after SetCollapsing:\n";
	gTranspose.printPredecessor();

	int num_cc = 0;
	for (auto i = 0; i < num_vertex_; i++) {
		if (gTranspose.getPredecessor(i) < 0) {
			std::cout << "SCC#" << ++num_cc << ": " << i << " ";
			for (auto j = 0; j < num_vertex_; j++) {
				if (gTranspose.getPredecessor(j) == i) {
					std::cout << j << " ";
				}
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;

	delete[] finishLargetoSmall;
}

void graph::Graph::TopologicalSort(int start)
{
	DFS(start);

	int* finishLargetoSmall = new int[num_vertex_];
	for (auto i = 0; i < num_vertex_; i++) {
		finishLargetoSmall[i] = i;
	}

	QuickSort(finish_, finishLargetoSmall, 0, num_vertex_ - 1);

	std::cout << "Topological Sort:" << std::endl;
	for (int i = 0; i < num_vertex_; i++)
		std::cout << std::setw(3) << finishLargetoSmall[i];
	std::cout << std::endl;
}
