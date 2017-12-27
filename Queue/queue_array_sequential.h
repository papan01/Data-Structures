#ifndef QUEUE_ARRAY_SEQUENTIAL_H
#define QUEUE_ARRAY_SEQUENTIAL_H

namespace queue
{
	template <class T>
	class QueueArraySequential
	{
	public:
		QueueArraySequential(const int& size = 5) : capacity_(size), front_(-1), back_(-1) 
		{
			queue_ = new T[capacity_];
		}

		~QueueArraySequential() { delete queue_; }

		void push(const T& x);
		void pop();
		int size();
		void resize(const T& x);
		bool isEmpty();
		bool isFull();
		T front();
		T back();
		

	private:
		/*
		* capacity_: array size
		* front_ : initialize -1
		* back_ : initialize -1
		*/
		int capacity_, front_, back_;
		T* queue_;
	};
}






#endif // !QUEUE_ARRAY_SEQUENTIAL_H

