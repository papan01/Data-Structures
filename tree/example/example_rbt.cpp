#include "red_black_tree.h"
#include <string>

int main()
{
	tree::RBT<std::string> rbt;
	rbt.insert(1000, "����");
	rbt.insert(999, "�F��");
	rbt.deleteNode(999);



	return 0;
}