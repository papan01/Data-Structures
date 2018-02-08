#include "hash_table_open_addressing.h"
#include <string>

int main()
{
	hash::HashTableOpenAddressing<std::string> hash(8);
	hash.insert(hash::Dictionary<std::string>(33, "blue"));          // 1,2,4,7,3,0,6,5 -> 1
	hash.insert(hash::Dictionary<std::string>(10, "yellow"));        // 2,3,5,0,4,1,7,6 -> 2
	hash.insert(hash::Dictionary<std::string>(77, "red"));           // 5,6,0,3,7,4,2,1 -> 5
	hash.insert(hash::Dictionary<std::string>(2, "white"));          // 2,3,5,0,4,1,7,6 -> 3
	hash.printTable();
	hash.insert(hash::Dictionary<std::string>(8, "black"));          // 0,1,3,6,2,7,5,4 -> 0
	hash.insert(hash::Dictionary<std::string>(47, "gray"));          // 7,0,2,5,1,6,4,3 -> 7
	hash.insert(hash::Dictionary<std::string>(90, "purple"));        // 2,3,5,0,4,1,7,6 -> 4
	hash.insert(hash::Dictionary<std::string>(1, "deep purple"));    // 4,5,7,2,6,3,1,0 -> 6
	hash.printTable();
	hash.insert(hash::Dictionary<std::string>(15, "green"));         // hash table overflow
	
	std::cout << "Search key(90)...:" << std::endl;
	hash.search(90);

	hash.deleteKey(90);
	std::cout << "After deleting key(90):" << std::endl;
	hash.printTable();
	std::cout << "Search key(90) again...:" << std::endl;
	hash.search(90);


	std::cin.get();
	return 0;
}