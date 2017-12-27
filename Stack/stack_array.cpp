#include <iostream>
#include "stack_array.h"

namespace stack
{
	template<class T>
	inline StackArray<T>::StackArray(int size) : top_(0), size_(size)
	{
		stack_ = new T[size_];
	}

	template<class T>
	void StackArray<T>::push(const T& x)
	{
		if (isFull())
		{
			std::cout << "Stack is full." << std::endl;
			return;
		}
		stack_[top_++] = x;
	}

	template<class T>
	void StackArray<T>::pop()
	{
		if (isEmpty())
			std::cout << "Stack is empty." << std::endl;
		top_--;
	}

	template<class T>
	int StackArray<T>::size()
	{
		return top_;
	}

	template<class T>
	bool StackArray<T>::isEmpty()
	{
		return top_ == 0;
	}

	template<class T>
	bool StackArray<T>::isFull()
	{
		return top_ == size_;
	}

	template<class T>
	T StackArray<T>::top()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty stack, can't find data." << std::endl;
			return -1;
		}
		return stack_[top_ - 1];
	}


	template class StackArray<int>;
}