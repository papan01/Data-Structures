#include "queue_linklist.h"
#include <iostream>

namespace queue
{
	template<class T>
	QueueList<T>::~QueueList()
	{
		QueueNode<T>* temp = new QueueNode<T>(0);
		while (front_ != nullptr)
		{
			temp = front_;
			front_ = front_->next;
			delete temp;
			temp = nullptr;
		}
	}

	template<class T>
	void QueueList<T>::push(const T & x)
	{
		if (isEmpty())
		{
			front_ = new QueueNode<T>(x);
			back_ = front_;
			size_++;
			return;
		}
		QueueNode<T>* newNode = new QueueNode<T>(x);
		back_->next = newNode;
		back_ = newNode;
		size_++;
	}

	template<class T>
	void QueueList<T>::pop()
	{
		if (isEmpty())
		{
			std::cout << "Queue is empty." << std::endl;
		}
		auto temp = front_;
		front_ = front_->next;
		delete temp;
		temp = nullptr;
		size_--;
	}

	template<class T>
	int QueueList<T>::size()
	{
		return size_;
	}

	template<class T>
	void QueueList<T>::clean()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, no need to clean." << std::endl;
			return;
		}
		QueueNode<T>* temp = new QueueNode<T>(0);
		while (front_ != nullptr)
		{
			temp = front_;
			front_ = front_->next;
			delete temp;
			temp = nullptr;
		}
		size_ = 0;
	}

	template<class T>
	bool QueueList<T>::isEmpty()
	{
		return size_ == 0;
	}

	template<class T>
	T QueueList<T>::front()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, can't find the data" << std::endl;
			return -1;
		}
		return front_->data;
	}

	template<class T>
	T QueueList<T>::back()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, can't find the data" << std::endl;
			return -1;
		}
		return back_->data;
	}

	template class QueueList<int>;
}