#include "hash_table_chaining.h"
#include <string>

int main()
{
	hash::HashTableChaining<std::string> hash(2);
	hash.insert(hash::HashNode<std::string>(12, "post rock"));
	hash.insert(hash::HashNode<std::string>(592, "shoegaze"));
	std::cout << "After inserting key(12),key(592):" << std::endl;
	hash.printTable();
	hash.insert(hash::HashNode<std::string>(6594, "blues"));
	std::cout << "After inserting key(6594), evoke TableDoubling():" << std::endl;
	hash.printTable();
	hash.insert(hash::HashNode<std::string>(7, "folk"));
	std::cout << "After inserting key(7):" << std::endl;
	hash.printTable();
	hash.insert(hash::HashNode<std::string>(123596, "hiphop"));
	std::cout << "After inserting key(123596), evoke TableDoubling():" << std::endl;
	hash.printTable();
	hash.insert(hash::HashNode<std::string>(93, "soul"));
	hash.insert(hash::HashNode<std::string>(2288, "indie"));
	hash.insert(hash::HashNode<std::string>(793, "jazz"));
	std::cout << "After inserting key(93),key(2288),key(793):" << std::endl;
	hash.printTable();
	hash.insert(hash::HashNode<std::string>(8491, "electro"));
	std::cout << "After inserting key(8491), evoke TableDoubling():" << std::endl;
	hash.printTable();
	hash.insert(hash::HashNode<std::string>(323359, "pop"));
	std::cout << "After inserting key(323359):" << std::endl;
	hash.printTable();

	std::cout << "Search key(8491)...:" << std::endl;
	hash.search(8491);
	std::cout << "Search key(7)...:" << std::endl;
	hash.search(7);
	hash.deleteKey(7);
	std::cout << "After deleting key(7):" << std::endl;
	std::cout << "Search key(7)...:" << std::endl;
	hash.search(7);

	hash.deleteKey(592);
	std::cout << "After deleting key(592):" << std::endl;
	hash.printTable();

	std::cout << "Want to  delete key(592) again:" << std::endl;
	hash.deleteKey(592);

	hash.deleteKey(123596);
	hash.deleteKey(323359);
	hash.deleteKey(793);
	hash.deleteKey(93);
	std::cout << "After deleting key(123596),key(323359),key(793),key(93):" << std::endl;
	hash.printTable();

	hash.deleteKey(6594);      
	std::cout << "After deleting key(6594), evoke TableShrinking():" << std::endl;
	hash.printTable();

	std::cin.get();
	return 0;
}