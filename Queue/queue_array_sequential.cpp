#include "queue_array_sequential.h"
#include <iostream>


namespace queue
{
	template<class T>
	void QueueArraySequential<T>::push(const T& x)
	{
		if (isFull())
		{
			std::cout << "Queue is full. You can't push anything." << std::endl;
			return;
		}
		queue_[++back_] = x;
	}

	template<class T>
	void QueueArraySequential<T>::pop()
	{
		if (isEmpty())
		{
			std::cout << "Queue is empty. You can't pop anything." << std::endl;
			return;
		}
		front_++;
	}

	template<class T>
	int QueueArraySequential<T>::size()
	{
		return back_ - front_;
	}

	template<class T>
	void QueueArraySequential<T>::resize(const T & x)
	{
		capacity_ = x;
		auto newQueue = new T[capacity_];
		auto j = 0;
		for (auto i = front_ + 1; i <= back_; i++)
		{
			newQueue[j] = queue_[i];
			j++;
		}
		
		front_ = -1;
		back_ = j - 1;
		delete queue_;
		queue_ = newQueue;
		std::cout << "Current capacity size: " << capacity_ << std::endl;
	}

	template<class T>
	bool QueueArraySequential<T>::isEmpty()
	{
		return front_ == back_;
	}

	template<class T>
	bool QueueArraySequential<T>::isFull()
	{
		return (back_ + 1) == capacity_ ;
	}

	template<class T>
	T QueueArraySequential<T>::front()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, can't find the data" << std::endl;
			return -1;
		}
		return queue_[front_+1];
	}

	template<class T>
	T QueueArraySequential<T>::back()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, can't find the data" << std::endl;
			return -1;
		}
		return queue_[back_];
	}

	template class QueueArraySequential<int>;
}