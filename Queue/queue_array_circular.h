#ifndef QUEUE_ARRAY_CIRCULAR_H
#define QUEUE_ARRAY_CIRCULAR_H

namespace queue
{
	template <class T>
	class QueueArrayCircular
	{
	public:
		QueueArrayCircular(const int& size = 5) : capacity_(size), front_(0), back_(0)
		{
			queue_ = new T[capacity_];
		}

		~QueueArrayCircular() { delete queue_; };

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
		* front_ : initialize 0
		* back_ : initialize 0
		*/
		int capacity_, front_, back_;
		T* queue_;
	};
}



#endif // !QUEUE_ARRAY_CIRCULAR_H

