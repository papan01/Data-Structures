#include "binary_search_tree.h"
#include <string>

int main()
{
	tree::BST<std::string> bst;
	bst.insert(513, "��J");
	bst.insert(8, "�t�P�H");
	bst.insert(1999, "����");
	bst.insert(2, "�J�L");
	bst.insert(79, "���O��");
	bst.insert(69, "���");
	bst.insert(888, "����");
	bst.insert(666, "��|");
	bst.insert(520, "16��");
	bst.insert(881, "�F��");
	bst.insert(999, "���Q");
	bst.insert(995, "����");
	


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