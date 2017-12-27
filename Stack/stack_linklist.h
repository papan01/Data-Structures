#ifndef STACK_LINKLIST_H
#define STACK_LINKLIST_H

namespace stack
{

	template<class T>
	class StackNode
	{
	public:
		T data;
		StackNode<T>* next;

		StackNode() : data(0), next(nullptr) {}
		StackNode(const T& data_ = 0, StackNode<T>* next_ = nullptr) : data(data_), next(next_) {}
	};

	template<class T>
	class StackList
	{
	public:
		StackList(const int& size) : top_(0), size_(size)
		{
			front_ = nullptr;
		}
		~StackList();

		void push(const T& x);
		void pop();
		int size();
		void clean();
		bool isEmpty();
		bool isFull();
		T top();

	private:
		int top_; //index for top stack item
		int size_; //stack size
		StackNode<T>* front_;	
	};

}




#endif // !STACK_LINKLIST_H

