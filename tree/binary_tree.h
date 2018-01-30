#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>


namespace tree
{
	template <class T>
	class BinaryTree;

	template <class T>
	class TreeNode
	{
	public:
		friend class BinaryTree<T>;
		TreeNode(T data = 0) : leftChild_(nullptr), rightChild_(nullptr), parent_(nullptr), data_(data) {}
	private:
		TreeNode<T>* leftChild_;
		TreeNode<T>* rightChild_;
		TreeNode<T>* parent_;
		T data_;
	};

	template <class T>
	class BinaryTree
	{
	public:
		TreeNode<T>* root;
		BinaryTree(TreeNode<T>* root_ = nullptr) : root(root_) {}
		BinaryTree(std::vector<T> data);
		~BinaryTree() { deleteTree(root); }


		void pre_order(TreeNode<T>* current_node);
		void in_order(TreeNode<T>* current_node);
		void post_order(TreeNode<T>* current_node);
		void level_order();

		TreeNode<T>* leftMost(TreeNode<T>* current_node);
		TreeNode<T>* rightMost(TreeNode<T>* current_node);

		TreeNode<T>* InorderSuccessor(TreeNode<T> *current);
		TreeNode<T>* InorderPredecessor(TreeNode<T> *current);

		void Inorder_by_parent(TreeNode<T> *root);
		void Inorder_Reverse(TreeNode<T> *root);
		void InsertLevelorder(T data);

		void deleteTree(TreeNode<T>* root_);
	};

	template<class T>
	BinaryTree<T>::BinaryTree(std::vector<T> data)
	{
		std::queue<TreeNode<T>*> q;
		root = new TreeNode<T>(data[0]);
		auto current_node = root;
		for (auto i = 1; i < static_cast<int>(data.size()); i+=2)
		{   
			if (data[i] != NULL )
			{
				//Left Child
				auto leftNode = new TreeNode<T>(data[i]);
				leftNode->parent_ = current_node;
				current_node->leftChild_ = leftNode;
				q.push(leftNode);
			}
	
			if (i + 1 >= static_cast<int>(data.size()))
				break;

			if (data[i + 1] != NULL)
			{
				//Right Child
				auto rightNode = new TreeNode<T>(data[i + 1]);
				rightNode->parent_ = current_node;
				current_node->rightChild_ = rightNode;
				q.push(rightNode);
			}

			current_node = q.front();
			q.pop();
		}
	}

	template<class T>
	void BinaryTree<T>::pre_order(TreeNode<T>* current_node)
	{
		if (current_node)
		{
			std::cout << std::setw(3) << current_node->data_ << " ";
			pre_order(current_node->leftChild_);
			pre_order(current_node->rightChild_);
		}
	}

	template<class T>
	void BinaryTree<T>::in_order(TreeNode<T>* current_node)
	{
		if (current_node)
		{	
			in_order(current_node->leftChild_);
			std::cout << std::setw(3) << current_node->data_ << " ";
			in_order(current_node->rightChild_);
		}
	}

	template<class T>
	void BinaryTree<T>::post_order(TreeNode<T>* current_node)
	{
		if (current_node)
		{
			post_order(current_node->leftChild_);
			post_order(current_node->rightChild_);
			std::cout << std::setw(3) << current_node->data_ << " ";
		}
	}

	template<class T>
	void BinaryTree<T>::level_order()
	{
		std::queue<TreeNode<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			auto current_node = q.front();
			q.pop();
			std::cout << std::setw(3) << current_node->data_ << " ";
			if (current_node->leftChild_ != nullptr)
				q.push(current_node->leftChild_);
			if (current_node->rightChild_ != nullptr)
				q.push(current_node->rightChild_);
		}
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::leftMost(TreeNode<T>* current_node)
	{
		while (current_node->leftChild_ != nullptr) 
		{
			current_node = current_node->leftChild_;
		}
		return current_node;
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::rightMost(TreeNode<T>* current_node)
	{
		while (current_node->rightChild_ != nullptr)
		{
			current_node = current_node->rightChild_;
		}
		return current_node;
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::InorderSuccessor(TreeNode<T>* current_node)
	{
		if (current_node->rightChild_ != nullptr)
			return leftMost(current_node->rightChild_);
		
		auto successor = current_node->parent_;
		while (successor != nullptr && current_node == successor->rightChild_)
		{
			current_node = successor;
			successor = successor->parent_;
		}
		return successor;
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::InorderPredecessor(TreeNode<T>* current_node)
	{
		if (current_node->leftChild_ != nullptr)
			return rightMost(current_node->leftChild_);

		auto predecessor = current_node->parent_;
		while (predecessor != nullptr && current_node == predecessor->leftChild_)
		{
			current_node = predecessor;
			predecessor = predecessor->parent_;
		}

		return predecessor;
	}

	template<class T>
	void BinaryTree<T>::Inorder_by_parent(TreeNode<T> * root)
	{
		auto first_node = leftMost(root);

		while (first_node)
		{
			std::cout << std::setw(3) << first_node->data_ << " ";
			first_node = InorderSuccessor(first_node);
		}
	}

	template<class T>
	void BinaryTree<T>::Inorder_Reverse(TreeNode<T> * root)
	{
		auto reverse_first_node = rightMost(root);
		while (reverse_first_node)
		{
			std::cout << std::setw(3) << reverse_first_node->data_ << " ";
			reverse_first_node = InorderPredecessor(reverse_first_node);
		}
	}

	template<class T>
	void BinaryTree<T>::InsertLevelorder(T data)
	{
		std::queue<TreeNode<T>*> q;
		auto current = root;

		while (current)
		{
			if (current->leftChild_ != nullptr)
				q.push(current->leftChild_);
			else
			{
				auto newNode = new TreeNode<T>(data);
				current->leftChild_ = newNode;
				newNode->parent_ = current;
				break;
			}

			if (current->rightChild_ != nullptr)
				q.push(current->rightChild_);
			else
			{
				auto newNode = new TreeNode<T>(data);
				current->rightChild_ = newNode;
				newNode->parent_ = current;
				break;
			}

			current = q.front();
			q.pop();
		}
	}

	template<class T>
	void BinaryTree<T>::deleteTree(TreeNode<T>* root_)
	{
		if (root_ == nullptr)
			return;
		deleteTree(root_->rightChild_);
		deleteTree(root_->leftChild_);
		delete root_;
	}
}




#endif // !TREE_H
