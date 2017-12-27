#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

namespace stack
{
	template<class T >
	class StackArray
	{
	public:
		StackArray(int size = 1);
		~StackArray() { delete stack_; }

		void push(const T& x);
		void pop();
		int size();
		bool isEmpty();
		bool isFull();
		T top();

	private:
		int top_; //index for top stack item
		int size_; //stack size
		T* stack_; 
	};

}
#endif // !STACK_ARRAY_H
