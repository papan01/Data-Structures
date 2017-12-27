#ifndef SORT
#define SORT
#include <vector>

//reference::https://www.geeksforgeeks.org/
//         ::http://alrightchiu.github.io/SecondRound/mu-lu-yan-suan-fa-yu-zi-liao-jie-gou.html


namespace sort
{
	template <class T>
	void swap(T& a, T& b)
	{
		auto temp = a;
		a = b;
		b = temp;
	}

	/*==============Insertion Sort=============*/
	template <class T>
	void InsertionSort(T* arr, const int& size)
	{
		for (auto i = 1; i < size; i++)
		{
			auto cur_value = arr[i];
			auto j = i - 1;
			while (cur_value < arr[j] && j >= 0)
			{
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = cur_value;
		}
	}
	/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

	/*==============Bubble Sort================*/
	template <class T>
	void BubbleSort(T* arr, const int& size)
	{
		for (auto i = 0; i < size - 1; i++) //compare n-1 times
		{
			for (auto j = 0; j < size - i - 1; j++)
			{
				if (arr[j] > arr[j + 1])
					swap(arr[j], arr[j + 1]);
			}
		}
	}
	/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

	/*==============Quick Sort=================*/
	template <class T>
	int Partition(T* arr,const int& left,const int& right)
	{
		auto pivot = arr[right];
		auto i = left - 1;
		for (auto j = left; j < right; j++)
		{
			if (arr[j] < pivot)
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		i++;
		swap(arr[i], arr[right]);
		return i;
	}

	template <class T>
	void QuickSort(T* arr, const int& left , const int& right)
	{
		if (left < right)
		{
			auto pivot_index = Partition(arr, left, right);
			QuickSort(arr, left, pivot_index - 1);
			QuickSort(arr, pivot_index + 1, right);
		}
	}
	/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

	/*==============Heap Sort==================*/
	template <class T>
	void MaxHeapify(std::vector<T>& arr,const int& root_index,const int& length)
	{
		auto left = 2 * root_index; //left child = index of root * 2
		auto right = 2 * root_index + 1; //right child = index of root * 2 + 1
		auto largest = 0;

		if (left <= length && arr[left] > arr[root_index])//left <= length: Judge child whether exist
			largest = left;
		else
			largest = root_index;

		if (right <= length && arr[right] > arr[largest])
			largest = right;

		if (largest != root_index)
		{
			swap(arr[largest], arr[root_index]);
			MaxHeapify(arr, largest, length);
		}
	}

	template <class T>
	void BuildMaxHeap(std::vector<T>& arr)
	{
		auto length = static_cast<int>(arr.size()); 

		for (auto i = length / 2; i >= 1; i--) //parent index = floor(child index / 2)
		{
			MaxHeapify(arr, i, length - 1);// heap store data from index 1 of array;
		}
	}

	template <class T>
	void HeapSort(std::vector<T>& arr)
	{
		arr.insert(arr.begin(), 0);

		BuildMaxHeap(arr);

		auto length = static_cast<int>(arr.size()) - 1;
		for (auto i = static_cast<int>(arr.size()) - 1; i > 1; i--)
		{
			swap(arr[1], arr[i]);
			length--;
			MaxHeapify(arr, 1, length);
		}
		
		arr.erase(arr.begin());
	}
	/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

	/*==============Merge Sort==================*/
	template <class T>
	void Merge(std::vector<T>& arr, int front, int mid, int end)
	{
		std::vector<T> LeftSub(arr.begin() + front, arr.begin() + mid + 1),
					   RightSub(arr.begin() + mid + 1, arr.begin() + end + 1);

		LeftSub.insert(LeftSub.end(), INT_MAX);      
		RightSub.insert(RightSub.end(),INT_MAX);

		auto index_left = 0, index_right = 0;


		for (int i = front; i <= end; i++) {

			if (LeftSub[index_left] <= RightSub[index_right]) {
				arr[i] = LeftSub[index_left];
				index_left++;
			}
			else {
				arr[i] = RightSub[index_right];
				index_right++;
			}
		}
	}

	template <class T>
	void MergeSort(std::vector<T> &arr, int front, int end)
	{
		if (front < end)
		{
			auto mid = (front + end) / 2;
			MergeSort(arr, front, mid);    
			MergeSort(arr, mid + 1, end);    
			Merge(arr, front, mid, end);  
		}
	}
	/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
}


#endif // !INSERTION_SORT

