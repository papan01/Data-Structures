#ifndef QUEUE_LINKLIST

namespace queue
{
	template<class T>
	class QueueNode
	{
	public:
		T data;
		QueueNode<T>* next;

		QueueNode() : data(0), next(nullptr) {}
		QueueNode(const T& data_ = 0, QueueNode<T>* next_ = nullptr) : data(data_), next(next_) {}
	};

	template<class T>
	class QueueList
	{
	public:
		QueueList() : size_(0), front_(nullptr), back_(nullptr) {}
		~QueueList();
		void push(const T& x);
		void pop();
		int size();
		void clean();
		bool isEmpty();
		T front();
		T back();


	private:
		int size_; //numbur of node
		QueueNode<T>* front_;
		QueueNode<T>* back_;
 	};


}





#endif // !QUEUE_LINKLIST

