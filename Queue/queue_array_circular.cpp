#include "queue_array_circular.h"
#include <iostream>

namespace queue
{
	template<class T>
	void QueueArrayCircular<T>::push(const T & x)
	{
		if (isFull())
		{
			std::cout << "Queue is full. You can't push anything." << std::endl;
			return;
		}

		back_ = (back_ + 1) % capacity_;
		queue_[back_] = x;
	}

	template<class T>
	void QueueArrayCircular<T>::pop()
	{
		if (isEmpty())
		{
			std::cout << "Queue is empty. You can't pop anything." << std::endl;
			return;
		}
		front_ = (++front_)%capacity_;
	}

	template<class T>
	int QueueArrayCircular<T>::size()
	{
		return front_ < back_ ? back_ - front_ : capacity_ - (front_ - back_);
	}

	template<class T>
	void QueueArrayCircular<T>::resize(const T & x)
	{
		capacity_ = x;
		auto newQueue = new T[capacity_];
		auto j = front_;
		auto size_ = size();
		for (auto i = 1; i <= size_; i++)
		{
			newQueue[i] = queue_[++j % capacity_];
		}
		back_ = size_;
		front_ = 0;
		delete queue_;
		queue_ = newQueue;
	}

	template<class T>
	bool QueueArrayCircular<T>::isEmpty()
	{
		return front_ == back_;
	}

	template<class T>
	bool QueueArrayCircular<T>::isFull()
	{
		return (back_ + 1)%capacity_ == front_ ;
	}

	template<class T>
	T QueueArrayCircular<T>::front()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, can't find the data" << std::endl;
			return -1;
		}
		return queue_[(front_ + 1)%capacity_];
	}

	template<class T>
	T QueueArrayCircular<T>::back()
	{
		if (isEmpty())
		{
			std::cout << "This is a empty queue, can't find the data" << std::endl;
			return -1;
		}
		return queue_[back_];
	}
	
	template class QueueArrayCircular<int>;
}