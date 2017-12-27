#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>


namespace tree
{
	template <class T>
	class TreeNode
	{
	public:
		TreeNode(T data_ = 0) : leftChild(nullptr), rightChild(nullptr), parent(nullptr), data(data_) {}
		TreeNode<T>* leftChild;
		TreeNode<T>* rightChild;
		TreeNode<T>* parent;
		T data;
	};

	template <class T>
	class BinaryTree
	{
	public:
		TreeNode<T>* root;
		BinaryTree(TreeNode<T>* root_ = nullptr) : root(root_) {}
		BinaryTree(std::vector<T> data);


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

	};

	template<class T>
	BinaryTree<T>::BinaryTree(std::vector<T> data)
	{
		std::queue<TreeNode<T>*> q;
		root = new TreeNode<T>(data[0]);
		auto current_node = root;
		for (auto i = 1; i < static_cast<int>(data.size()); i+=2)
		{   
			//leftChild
			auto leftNode = new TreeNode<T>(data[i]);
			leftNode->parent = current_node;
			current_node->leftChild = leftNode;
			q.push(leftNode);

			if (i + 1 >= static_cast<int>(data.size()))
				break;

			//rightChild
			auto rightNode = new TreeNode<T>(data[i + 1]);
			rightNode->parent = current_node;
			current_node->rightChild = rightNode;
			q.push(rightNode);

			current_node = q.front();
			q.pop();
		}
	}

	template<class T>
	void BinaryTree<T>::pre_order(TreeNode<T>* current_node)
	{
		if (current_node)
		{
			std::cout << std::setw(3) << current_node->data << " ";
			pre_order(current_node->leftChild);
			pre_order(current_node->rightChild);
		}
	}

	template<class T>
	void BinaryTree<T>::in_order(TreeNode<T>* current_node)
	{
		if (current_node)
		{	
			in_order(current_node->leftChild);
			std::cout << std::setw(3) << current_node->data << " ";
			in_order(current_node->rightChild);
		}
	}

	template<class T>
	void BinaryTree<T>::post_order(TreeNode<T>* current_node)
	{
		if (current_node)
		{
			post_order(current_node->leftChild);
			post_order(current_node->rightChild);
			std::cout << std::setw(3) << current_node->data << " ";
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
			std::cout << std::setw(3) << current_node->data << " ";
			if (current_node->leftChild != nullptr)
				q.push(current_node->leftChild);
			if (current_node->rightChild != nullptr)
				q.push(current_node->rightChild);
		}
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::leftMost(TreeNode<T>* current_node)
	{
		while (current_node->leftChild != nullptr) 
		{
			current_node = current_node->leftChild;
		}
		return current_node;
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::rightMost(TreeNode<T>* current_node)
	{
		while (current_node->rightChild != nullptr)
		{
			current_node = current_node->rightChild;
		}
		return current_node;
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::InorderSuccessor(TreeNode<T>* current_node)
	{
		if (current_node->rightChild != nullptr)
			return leftMost(current_node->rightChild);
		
		auto successor = current_node->parent;
		while (successor != nullptr && current_node == successor->rightChild)
		{
			current_node = successor;
			successor = successor->parent;
		}
		return successor;
	}

	template<class T>
	TreeNode<T>* BinaryTree<T>::InorderPredecessor(TreeNode<T>* current_node)
	{
		if (current_node->leftChild != nullptr)
			return rightMost(current_node->leftChild);

		auto predecessor = current_node->parent;
		while (predecessor != nullptr && current_node == predecessor->leftChild)
		{
			current_node = predecessor;
			predecessor = predecessor->parent;
		}

		return predecessor;
	}

	template<class T>
	void BinaryTree<T>::Inorder_by_parent(TreeNode<T> * root)
	{
		auto first_node = leftMost(root);

		while (first_node)
		{
			std::cout << std::setw(3) << first_node->data << " ";
			first_node = InorderSuccessor(first_node);
		}
	}

	template<class T>
	void BinaryTree<T>::Inorder_Reverse(TreeNode<T> * root)
	{
		auto reverse_first_node = rightMost(root);
		while (reverse_first_node)
		{
			std::cout << std::setw(3) << reverse_first_node->data << " ";
			reverse_first_node = InorderPredecessor(reverse_first_node);
		}
	}
}




#endif // !TREE_H
