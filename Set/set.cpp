#include "set.h"
#include <iostream>
#include <iomanip>

namespace set
{
	int Set::FindSetCollapsing(int i)
	{
		auto root = 0;
		for (root = i; set_[root] >= 0; root = set_[root]); //find root

		// collapsing
		while (i != root) 
		{           
			int parent = set_[i];
			set_[i] = root;
			i = parent;
		}

		return root;
	}


	void Set::UnionSet(int x, int y)
	{
		auto xroot = FindSetCollapsing(x);
		auto yroot = FindSetCollapsing(y);

		//Compare two subset which rank(height) small than another.
		//root value necessarily is negative.
		//The more negative expresses the heighter.
		if (set_[xroot] <= set_[yroot]) {
			set_[xroot] += set_[yroot];
			set_[yroot] = xroot;
		}
		else 
		{    
			set_[yroot] += set_[xroot];
			set_[xroot] = yroot;
		}
	}

	void Set::PrintSet()
	{
		for (auto i = 0; i < size_; i++)
		{
			std::cout << std::setw(3) << i;
		}
		std::cout << std::endl;
		for (auto i = 0; i < size_; i++)
		{
			std::cout << std::setw(3) << set_[i];
		}
		std::cout << std::endl;
	}
}