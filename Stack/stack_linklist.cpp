#include "stack_linklist.h"
#include <iostream>

namespace stack
{
	template<class T>
	StackList<T>::~StackList()
	{
		StackNode<T>* temp = new StackNode<T>(0);
		while (front_ != nullptr)
		{
			temp = front_;
			front_ = front_->next;
			delete temp;
			temp = nullptr;
		}
	}

	template<class T>
	void StackList<T>::push(const T & x)
	{
		if (isFull())
		{
			std::cout << "Stack is full. You can't push anything." << std::endl;
			return;
		}

		if (isEmpty())
		{
			front_ = new StackNode<T>(x);
			top_++;
			return;
		}

		StackNode<T>* newNode = new StackNode<T>(x);
		newNode->next = front_;
		front_ = newNode;
		top_++;
	}

	template<class T>
	void StackList<T>::pop()
	{
		if (isEmpty())
		{
			std::cout << "Stack is empty. You can't pop anything." << std::endl;
			return;
		}
		auto temp = front_;
		front_ = front_->next;
		delete temp;
		temp = nullptr;
		top_--;
	}

	template<class T>
	int StackList<T>::size()
	{
		return top_;
	}

	template<class T>
	void StackList<T>::clean()
	{
		if (front_ == nullptr)
		{
			std::cout << "This is a empty stack, no need to clean." << std::endl;
			return;
		}
		StackNode<T>* temp = new StackNode<T>(0);
		while (front_ != nullptr)
		{
			temp = front_;
			front_ = front_->next;
			delete temp;
			temp = nullptr;
		}
		top_ = 0;
	}

	template<class T>
	bool StackList<T>::isEmpty()
	{
		return top_ == 0;
	}

	template<class T>
	bool StackList<T>::isFull()
	{
		return top_ == size_;
	}

	template<class T>
	T StackList<T>::top()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty stack, can't find data." << std::endl;
			return -1;
		}
		return front_->data;
	}

	template class StackList<int>;
}