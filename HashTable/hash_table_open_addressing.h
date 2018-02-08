#ifndef HASH_TABLE_OPEN_ADDRESSING_H
#define HASH_TABLE_OPEN_ADDRESSING_H

#include <iostream>

namespace hash
{
	template <class T>
	class Dictionary
	{
	public:
		int key;
		T value;

		Dictionary() : key(0), value(T{}) {}
		Dictionary(const int& key_ , const T& value_) : key(key_),value(value_) {}
		Dictionary(const Dictionary& dict) : key(dict.key), value(dict.value) {}
	};

	template <class T>
	class HashTableOpenAddressing
	{
	public:
		HashTableOpenAddressing(int size) : size_(size), count_(0)
		{
			table_ = new Dictionary<T> [size_];
		}
		~HashTableOpenAddressing();

		void insert(const Dictionary<T>& dict);
		void deleteKey(const int& key);
		void search(const int& key);
		void printTable();

	private:
		int size_, count_;
		Dictionary<T>* table_;

		int quadraticProbing(int key, int i);
	};


	template<class T>
	HashTableOpenAddressing<T>::~HashTableOpenAddressing()
	{
		delete[] table_;
		table_ = nullptr;
	}

	template<class T>
	void HashTableOpenAddressing<T>::insert(const Dictionary<T>& dict)
	{
		int i = 0;
		while (i != size_)
		{
			auto index = quadraticProbing(dict.key, i);
			if (table_[index].key ==  0)
			{
				table_[index].key = dict.key;
				table_[index].value = dict.value;
				count_++;
				return;
			}
			else
				i++;
		}
		std::cout << "Hash table overflow." << std::endl;
	}

	template<class T>
	void HashTableOpenAddressing<T>::deleteKey(const int & key)
	{
		int i = 0;
		while (i != size_)
		{
			auto index = quadraticProbing(key, i);
			if (table_[index].key == key)
			{
				table_[index].key = 0;
				table_[index].value = T{};
				count_--;
				return;
			}
			else
				i++;
		}
	}

	template<class T>
	void HashTableOpenAddressing<T>::search(const int & key)
	{
		int i = 0;
		while (i != size_)
		{
			auto index = quadraticProbing(key, i);
			if (table_[index].key == key)
			{
				std::cout << table_[index].value << std::endl << std::endl;
				return;
			}
			else
				i++;
		}
		std::cout << "data not found." << std::endl << std::endl;
	}

	template<class T>
	void HashTableOpenAddressing<T>::printTable()
	{
		for (auto i = 0; i < size_; i++) {
			std::cout << "slot#" << i << ": (" << table_[i].key
				<< "," << table_[i].value << ")" << std::endl;
		}
		std::cout << std::endl;
	}

	template<class T>
	int HashTableOpenAddressing<T>::quadraticProbing(int key, int i)
	{
		// c1 = c2 = 0.5
		return static_cast<int>(((key % size_) + 0.5*i + 0.5*i*i)) % size_;
	}
}




#endif // !HASH_TABLE_OPEN_ADDRESSING_H

