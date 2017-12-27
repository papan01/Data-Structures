#ifndef SET_H
#define SET_H

namespace set
{
	class Set
	{
	public:
		Set(int* set, const int& size) : set_(set) , size_(size) {}
		~Set() { delete set_; }

		int FindSetCollapsing(int i);
		void UnionSet(int x, int y);
		void PrintSet();
	private:
		int* set_;
		const int size_;
	};
}



#endif // !SET_H

