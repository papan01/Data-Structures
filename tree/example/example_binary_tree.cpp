#include "binary_tree.h"
#include <string>

int main()
{

	std::vector<char> data{ 'A','B','C','D','E','F',NULL,NULL,NULL,'G','H',NULL,'I'};
	tree::BinaryTree<char> T(data);


	std::cout << "Pre-order: " << std::endl;
	T.pre_order(T.root);
	std::cout << std::endl;
	std::cout << "In-order: " << std::endl;
	T.in_order(T.root);
	std::cout << std::endl;
	std::cout << "Post-order: " << std::endl;
	T.post_order(T.root);
	std::cout << std::endl;
	std::cout << "Level-order: " << std::endl;
	T.level_order();
	std::cout << std::endl;
	std::cout << "In-order by parent: " << std::endl;
	T.Inorder_by_parent(T.root);
	std::cout << std::endl;
	std::cout << "Reverse in-order: " << std::endl;
	T.Inorder_Reverse(T.root);
	std::cout << std::endl;

	T.InsertLevelorder('J');
	T.InsertLevelorder('K');
	T.InsertLevelorder('L');
	T.InsertLevelorder('M');

	std::cout << "Level-order: " << std::endl;
	T.level_order();
	std::cout << std::endl;
	std::cout << "In-order by parent: " << std::endl;
	T.Inorder_by_parent(T.root);
	std::cout << std::endl;
	std::cin.get();
	return 0;
}