#include "binary_search_tree.h"
#include <string>

int main()
{
	tree::BST<std::string> bst;
	bst.insert(513, "比克");
	bst.insert(8, "龜仙人");
	bst.insert(1999, "悟空");
	bst.insert(2, "克林");
	bst.insert(79, "弗力扎");
	bst.insert(69, "基紐");
	bst.insert(888, "悟飯");
	bst.insert(666, "西魯");
	bst.insert(520, "16號");
	bst.insert(881, "達爾");
	bst.insert(999, "普烏");
	bst.insert(995, "撒旦");
	


	std::cout << "Inorder Traversal:" << std::endl;
	bst.in_order();
	std::cout << std::endl;
	std::cout << "Level-order Traversal:" << std::endl;
	bst.level_order();
	std::cout << std::endl;

	auto test_node_1 = bst.search(1999);
	if (test_node_1 != nullptr)
	{
		std::cout << "Found the element: " << test_node_1->getValue() << "(" << test_node_1->getKey() << ")" << std::endl;
	}
	else
	{
		std::cout << "No element exist." << std::endl;
	}


	bst.remove(666);
	std::cout << "Level-order Traversal:" << std::endl;
	bst.level_order();
	std::cout << std::endl;

	std::cin.get();
	return 0;
}