#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
using std::cout;
using std::endl;

template<class T>
class ListNode{
public:
	T data;
	ListNode<T> *next;
	ListNode() :data(0), next(nullptr){};
	ListNode(const T& item, ListNode<T>* ptrnext = nullptr) :data(item), next(ptrnext){};
};

template<class T>
class LinkedList{
private:
	int size;
	ListNode<T> *front;
	ListNode<T> *rear;
public:
	LinkedList() :size(0), front(nullptr), rear(nullptr){};
	void PrintList();
	void InsertFront(T item);
	void InsertRear(T item);
	void Delete(T item);
	void Size();
	void Clean();
	void Reverse();
};

//========================definition===========================//
template<class T>
void LinkedList<T>::PrintList()
{
	if (front == nullptr)
	{
		cout << "List is empty." << endl;
	}
	else
	{
		ListNode<T>* temp = front;
		while (temp != nullptr)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}

template<class T>
void LinkedList<T>::InsertFront(T item)
{
	ListNode<T>* newNode = new ListNode<T>(item);
	if (front != nullptr)
	{
		newNode->next = front;
		front = newNode;
	}
	else
	{
		front = newNode;
		rear = front;
	}
	size++;
}

template<class T>
void LinkedList<T>::InsertRear(T item)
{
	ListNode<T>* newNode = new ListNode<T>(item);
	if (rear != nullptr)
	{
		rear->next = newNode;
		rear = newNode;
	}
	else
	{
		rear = newNode;
		front = rear;
	}
	size++;
}

template<class T>
void LinkedList<T>::Delete(T item)
{
	ListNode<T>* temp = new ListNode<T>(), *previous_temp = new ListNode<T>();
	if (front->data == item)
	{
		temp = front;
		front = temp->next;
		delete temp;
		temp = nullptr;
		size--;
	}
	else if (rear->data == item)
	{
		temp = front;
		while (temp->next != rear)
		{
			temp = temp->next;
		}
		temp->next = nullptr;
		rear = temp;
		size--;
	}
	else
	{
		temp = front->next;
		previous_temp = nullptr;
		while (temp != nullptr && temp->data != item)
		{
			previous_temp = temp;
			temp = temp->next;
		}
		if (temp == nullptr)
		{
			cout << "Can't find the item." << endl;
		}
		else
		{
			previous_temp->next = temp->next;
			delete temp;
			temp = nullptr;
			size--;
		}
	}
}

template<class T>
void LinkedList<T>::Size()
{
	cout << "Length: " << size << endl;
}

template<class T>
void LinkedList<T>::Clean()
{
	if (front == nullptr)
	{
		cout << "This is a empty list,no need to clean." << endl;
	}
	else
	{
		ListNode<T>* temp = new ListNode<T>();
		while (front != nullptr)
		{
			temp = front;
			front = front->next;
			delete temp;
			temp = nullptr;
		}
	}
}

template<class T>
void LinkedList<T>::Reverse()
{
	if (front == nullptr)
	{
		cout << "This is a empty list,you can't reverse." << endl;
	}
	else
	{
		ListNode<T>* temp = new ListNode<T>(), *previous_temp = new ListNode<T>(), *preceding_temp = new ListNode<T>();
		previous_temp = nullptr;
		temp = front;
		rear = temp;
		preceding_temp = front->next;
		while (preceding_temp != nullptr)
		{
			temp->next = previous_temp;
			previous_temp = temp;
			temp = preceding_temp;
			preceding_temp = preceding_temp->next;
		}

		temp->next = previous_temp;
		front = temp;
	}
}

#endif