#include "red_black_tree.h"
#include <string>

int main()
{
	tree::RBT<std::string> rbt;
	rbt.insert(1000, "®©ªÅ");
	rbt.insert(999, "¹Fº¸");
	rbt.deleteNode(999);



	return 0;
}