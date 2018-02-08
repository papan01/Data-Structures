#ifndef HASH_TABLE_CHAINING_H
#define HASH_TABLE_CHAINING_H
#include <iostream>
#include <math.h> 

namespace hash
{
	template <class T>
	class HashNode
	{
	public:
		int key;
		T value;
		HashNode* next;

		HashNode(const int& key_, const T& value_) : key(key_), value(value_), next(nullptr) {}
		HashNode(const HashNode& node) : key(node.key), value(node.value), next(node.next) {}
	};

	template <class T>
	class HashTableChaining
	{
	public:

		HashTableChaining(int size) : size_(size), count_(0)
		{
			table_ = new HashNode<T> *[size_]();
		}
		~HashTableChaining();

		void insert(const HashNode<T> node);
		void deleteKey(const int& key);
		void search(const int& key);
		void printTable();

	private:
		int size_, count_;
		HashNode<T>** table_;


		//Hash Function
		//In this case, using multiplication method
		int multiplication_method(const int& key);

		void tableDoubling();
		void tableShrinking();
		void rehashing(int size_org);
	};


	template<class T>
	HashTableChaining<T>::~HashTableChaining()
	{
		for (auto i = 0; i < size_; i++) {    // visit every node in table											
			auto current = table_[i];          // and release the memory of each node
			while (current != nullptr)		  // point *current to first node in list
			{								  // traversal in list
				auto previous = current;     
				current = current->next;
				delete previous;   
				previous = nullptr;
			}
		}
		delete[] table_;
	}

	template<class T>
	void HashTableChaining<T>::insert(const HashNode<T> node)
	{
		count_++;
		if (count_ > size_)			// consider load factor
			tableDoubling();	    // if n/m > 1, then double the size of table

		auto index = multiplication_method(node.key);
		auto newNode = new HashNode<T>(node);

		if (table_[index] == nullptr)
			table_[index] = newNode;
		else
		{
			auto next = table_[index]->next;
			table_[index]->next = newNode;
			newNode->next = next;
		}

	}

	template<class T>
	void HashTableChaining<T>::deleteKey(const int & key)
	{
		auto index = multiplication_method(key);
		auto current = table_[index];
		HashNode<T>* previous = nullptr;

		while (current != nullptr && current->key != key) {
			previous = current;               // traversal in list, 3 cases:
			current = current->next;          // 1. data not found
		}                                     // 2. data found at first node in list
											  // 3. data found at other position in list

		if (current == nullptr)
		{
			std::cout << "Data not found." << std::endl;
			return;
		}
		else
		{
			if (previous == nullptr)	
				// eg: list:5->2->9->NULL, want to delete 5
				// after deleting 5, list:2->9->nullptr
				// current points to 5 
				table_[index] = current->next;		
			else
				// eg: list:5->2->9->NULL, want to delete 2
				// after deleting 2, list:5->9->NULL
				// current points to 2
				previous->next = current->next;

			delete current;
			current = nullptr;
		}

		count_--;
		if (count_ < size_ / 4) {  // consider load factor
			tableShrinking();      // if n/m < 4, then shrink the table
		}

	}

	template<class T>
	void HashTableChaining<T>::search(const int & key)
	{
		auto index = multiplication_method(key);
		auto current = table_[index];

		while (current != nullptr)
		{
			if (current->key == key)
			{
				std::cout << current->value << std::endl << std::endl;
				return;
			}
			current = current->next;
		}
		
		std::cout << "data not found." << std::endl << std::endl;
	}

	template<class T>
	void HashTableChaining<T>::printTable()
	{
		for (auto i = 0; i < size_; i++) {    // visit every node in table 
			std::cout << "#slot#" << i << ": ";
			auto current = table_[i];
			while (current != nullptr) {
				std::cout << "(" << current->key << "," << current->value << ") ";
				current = current->next;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	template<class T>
	int HashTableChaining<T>::multiplication_method(const int & key)
	{
		double A = 0.6180339887,
			frac = key*A - floor(key*A);
		return static_cast<int>(floor(this->size_*frac));
	}

	template<class T>
	void HashTableChaining<T>::tableDoubling()
	{
		int size_org = size_;    // size_orig represents the original size of table
		size_ *= 2;              // double the size of table
		rehashing(size_org);;    // create new table with new larger size
	}

	template<class T>
	void HashTableChaining<T>::tableShrinking()
	{
		int size_org = size_;    // size_orig represents the original size of table
		size_ /= 2;              // shrink the size of table
		rehashing(size_org);;    // create new table with new smaller size
	}

	template<class T>
	void HashTableChaining<T>::rehashing(int size_org)
	{
		auto newTable = new HashNode<T> *[size_]();

		for (auto i = 0; i < size_org; i++) // visit every node in the original table
		{
			auto curr_org = table_[i];      // curr_orig: current node in original table
			HashNode<T>* prev_org = nullptr;        // prev_orig: following curr_orig 

			while (curr_org != nullptr)
			{
				prev_org = curr_org->next;  // curr_orig will be directly move to new table
											// need prev_orig to keep pointer in original table

				auto index = multiplication_method(curr_org->key);    // get index of slot in new table

				// push_front(), do not allocate new memory space for data
				// directly move node in original table to new table
				if (newTable[index] == nullptr) {       // means newtable[index] is empty
					newTable[index] = curr_org;
					newTable[index]->next = nullptr;       // equivalent to curr_orig->next = nullptr;
				}
				// if there is no initialization for newtable, segmentation faults might happen
				// because newtable[index] might not point to NULL 
				// but newtable[index] is empty
				else {                                   // if newtable[index] is not empty
					auto next = newTable[index]->next;  // push_front()
					newTable[index]->next = curr_org;
					curr_org->next = next;
				}
				curr_org = prev_org;          // visit the next node in list in original table
			}
		}
		delete[] table_;                // release memory of original table
		this->table_ = newTable;        // point table of object to new table
	}
}







#endif // !HASH_TABLE_CHAINING_H

