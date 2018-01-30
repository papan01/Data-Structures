#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <memory>
#include <queue>
#include <iostream>
#include <iomanip>

namespace tree
{

	template <class T>
	class BST;

	template <class T>
	class BSTreeNode
	{
	public:
		friend class BST<T>;
		BSTreeNode(int key = 0,T data = 0) :leftChild_(nullptr), rightChild_(nullptr), parent_(nullptr), data_(data), key_(key) {}

		int getKey() const { return key_; }
		T getValue() const { return data_; }
	private:
		std::shared_ptr<BSTreeNode<T>> leftChild_;
		std::shared_ptr<BSTreeNode<T>> rightChild_;
		std::shared_ptr<BSTreeNode<T>> parent_;
		T data_;
		int key_;
	};

	template <class T>
	class BST
	{
	public:
		BST(std::shared_ptr<BSTreeNode<T>> root = nullptr) : root_(root) {}
		
		std::shared_ptr<BSTreeNode<T>> search(int key);
		void insert(int key, T value);
		void in_order();
		void level_order();
		void remove(int key);

	private:
		std::shared_ptr<BSTreeNode<T>> root_;
		std::shared_ptr<BSTreeNode<T>> leftMost(std::shared_ptr<BSTreeNode<T>> current_node);
		std::shared_ptr<BSTreeNode<T>> successor(std::shared_ptr<BSTreeNode<T>> current_node);
		
	};


	template<class T>
	std::shared_ptr<BSTreeNode<T>> BST<T>::search(int key)
	{
		auto current_node = root_;
		while (current_node != nullptr && key != current_node->key_)
		{
			if (key < current_node->key_)
				current_node = current_node->leftChild_;
			else
				current_node = current_node->rightChild_;
		}

		return current_node;
	}

	template<class T>
	void BST<T>::insert(int key, T value)
	{
		std::shared_ptr<BSTreeNode<T>> x = root_;
		std::shared_ptr<BSTreeNode<T>> y;
		auto insert_node = std::make_shared<BSTreeNode<T>>(key, value);
		
		while (x != nullptr)
		{
			y = x;
			if (insert_node->key_ < x->key_)
				x = x->leftChild_;
			else
				x = x->rightChild_;
		}

		insert_node->parent_= y;

		if (y == nullptr)
		{
			root_ = insert_node;
		}
		else if (insert_node->key_ < y->key_) {
			y->leftChild_ = insert_node;
		}
		else {
			y->rightChild_ = insert_node;
		}
	}

	template<class T>
	void BST<T>::in_order()
	{
		auto current_node = leftMost(root_);

		while (current_node)
		{
			std::cout << std::setw(3) << current_node->data_ << "(" << current_node->key_ << ")" << " ";
			current_node = successor(current_node);
		}
	}

	template<class T>
	void BST<T>::level_order()
	{
		std::queue<std::shared_ptr<BSTreeNode<T>>> q;
		q.push(root_);
		while (!q.empty())
		{
			auto current_node = q.front();
			q.pop();
			std::cout << std::setw(3) << current_node->data_ << "(" << current_node->key_ << ")" << " ";
			if (current_node->leftChild_ != nullptr)
				q.push(current_node->leftChild_);
			if (current_node->rightChild_ != nullptr)
				q.push(current_node->rightChild_);		 
		}
	}

	template<class T>
	void BST<T>::remove(int key)
	{
		auto delete_node = search(key);
		if (delete_node == nullptr)
		{
			std::cout << "data not found." << std::endl;
			return;
		}

		std::shared_ptr<BSTreeNode<T>> y; //�u���n�Q�R��������O���骺node
		std::shared_ptr<BSTreeNode<T>> x; //�Q�R��node��child(�i�H�Oleft�Ϊ�right)

		
		/* �g�L�U�C����if-else����A�i�N���D��Ѧ�:
		* if(delete_node->leftChild_ == nullptr || delete_node->rightChild_ == nullptr)
		*	case1: delete_node �S��child
		*	case2: delete_node �u���@��child
		* else 
		*	case3:��delete_node�����child�A�z�L�u�㦳���child��node��Successor�άOPredecessor�@�w�Oleaf node�άO�u���@��child�v
		*         �O�Ҧܦh�u���@��child�A�Ny��@delete_node������
		*/
		if (delete_node->leftChild_ == nullptr || delete_node->rightChild_ == nullptr)
			y = delete_node;
		else
			y = successor(delete_node);

		//�Nx�]��y��child
		if (y->leftChild_ != nullptr)
			x = y->leftChild_;
		else 
			x = y->rightChild_;

		//�by�R���e�A��x����BST�W
		if (x != nullptr)
			x->parent_ = y->parent_;

		// �Y�R�����O�����root, �N��x���s��root
		if (y->parent_ == nullptr)                
			root_ = x;
		else if(y == y->parent_->leftChild_)
			y->parent_->leftChild_ = x;
		else
			y->parent_->rightChild_ = x;
	
		if (y != delete_node) {					  // �Yy�Odelete_node������, �̫�n�A�Ny�����
			delete_node->key_ = y->key_;          // ��^delete_node���O�����m, �ñNy���O�����m����
			delete_node->data_ = y->data_; 
		}

		y.~shared_ptr();
		y = nullptr;
	}

	template<class T>
	std::shared_ptr<BSTreeNode<T>> BST<T>::leftMost(std::shared_ptr<BSTreeNode<T>> current_node)
	{
		while (current_node->leftChild_ != nullptr)
		{
			current_node = current_node->leftChild_;
		}
		return current_node;
	}

	template<class T>
	std::shared_ptr<BSTreeNode<T>> BST<T>::successor(std::shared_ptr<BSTreeNode<T>> current_node)
	{
		if (current_node->rightChild_ != nullptr)
			return leftMost(current_node->rightChild_);

		auto successor_node = current_node->parent_;
		while (successor_node != nullptr && current_node == successor_node->rightChild_)
		{
			current_node = successor_node;
			successor_node = successor_node->parent_;
		}
		return successor_node;
	}

}


#endif // !BINARY_SEARCH_TREE_H

