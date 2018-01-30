#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include <memory>
#include <queue>
#include <iostream>
#include <iomanip>


namespace tree
{
	template <class T>
	class RBT;

	template <class T>
	class RBTreeNode
	{
	public:
		enum 
		{
			RED,
			BLACK
		};

		RBTreeNode() : leftChild_(nullptr), rightChild_(nullptr), parent_(nullptr), key_(0), color_(BLACK) {}
		RBTreeNode(int key , T data, int color = RED) : leftChild_(nullptr), rightChild_(nullptr), parent_(nullptr), key_(key), data_(data), color_(color) {}
		int getKey() const { return key_; }
		T getValue() const { return data_; }

		friend class RBT<T>;
	private:
		std::shared_ptr<RBTreeNode<T>> leftChild_;
		std::shared_ptr<RBTreeNode<T>> rightChild_;
		std::shared_ptr<RBTreeNode<T>> parent_;
		T data_;
		int key_;
		int color_; // 0 : red , 1 : black 
	};

	template <class T>
	class RBT
	{
	public:
		RBT()
		{
			nil_ = std::make_shared<RBTreeNode<T>>();
			root_ = nil_;
			root_->parent_ = nil_;
		}

		void insert(int key, T value);
		void deleteNode(int key);
	private:
		std::shared_ptr<RBTreeNode<T>> root_;
		std::shared_ptr<RBTreeNode<T>> nil_; //sentinel

		std::shared_ptr<RBTreeNode<T>> search(int key);
		void leftRotation(std::shared_ptr<RBTreeNode<T>> current_node);
		void rightRotation(std::shared_ptr<RBTreeNode<T>> current_node);
		void insert_modifyColor(std::shared_ptr<RBTreeNode<T>> current_node);
		void delete_modifyColor(std::shared_ptr<RBTreeNode<T>> current_node);

		std::shared_ptr<RBTreeNode<T>> successor(std::shared_ptr<RBTreeNode<T>> current_node);
		std::shared_ptr<RBTreeNode<T>> leftMost(std::shared_ptr<RBTreeNode<T>> current_node);
	};

	template<class T>
	void RBT<T>::insert(int key, T value)
	{
		std::shared_ptr<RBTreeNode<T>> x = root_;
		std::shared_ptr<RBTreeNode<T>> y = nil_;
		auto insert_node = std::make_shared<RBTreeNode<T>>(key, value);

		while (x != nil_)
		{
			y = x;
			if (insert_node->key_ < x->key_)
				x = x->leftChild_;
			else
				x = x->rightChild_;
		}

		insert_node->parent_ = y;

		if (y == nil_)
			root_ = insert_node;
		else if (insert_node->key_ < y->key_) 
			y->leftChild_ = insert_node;
		else 
			y->rightChild_ = insert_node;

		insert_node->leftChild_ = nil_;
		insert_node->rightChild_ = nil_;
		//insert_node->color_ = RBTreeNode<T>::RED; construct doing

		insert_modifyColor(insert_node);
	}

	template<class T>
	void RBT<T>::deleteNode(int key)
	{
		auto delete_node = search(key);
		if (delete_node == nullptr)
		{
			std::cout << "data not found." << std::endl;
			return;
		}

		std::shared_ptr<RBTreeNode<T>> y; //真正要被刪除並釋放記憶體的node
		std::shared_ptr<RBTreeNode<T>> x; //被刪除node的child(可以是left或者right)

		/* 經過下列此組if-else之後，可將問題拆解成:
		 * if(delete_node->leftChild_ == nullptr || delete_node->rightChild_ == nullptr)
		 *	  case1: delete_node 沒有child
		 *	  case2: delete_node 只有一個child
		 * else
		 *	  case3:當delete_node有兩個child，透過「具有兩個child的node的Successor或是Predecessor一定是leaf node或是只有一個child」
		 *          保證至多只有一個child，將y當作delete_node的替身
		 */
		if (delete_node->leftChild_ == nil_ || delete_node->rightChild_ == nil_)
			y = delete_node;
		else
			y = successor(delete_node);

		//將x設為y的child
		if (y->leftChild_ != nil_)
			x = y->leftChild_;
		else
			x = y->rightChild_;

		//即使x是NIL也要把x的parent指向有效的記憶體位置
		//因為在FixUp時需要藉由x->parent判斷x為leftchild或是rightchild
		x->parent_ = y->parent_;

		// 若刪除的是原先的root, 就把x當成新的root
		if (y->parent_ == nil_)
			root_ = x;
		else if (y == y->parent_->leftChild_)
			y->parent_->leftChild_ = x;
		else
			y->parent_->rightChild_ = x;

		if (y != delete_node) {					  // 若y是delete_node的替身, 最後要再將y的資料
			delete_node->key_ = y->key_;          // 放回delete_node的記憶體位置, 並將y的記憶體位置釋放
			delete_node->data_ = y->data_;
		}

		if (y->color_ == RBTreeNode<T>::BLACK)
			delete_modifyColor(x);
	}

	template<class T>
	std::shared_ptr<RBTreeNode<T>> RBT<T>::search(int key)
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
	void RBT<T>::leftRotation(std::shared_ptr<RBTreeNode<T>> x)
	{
		auto y = x->rightChild_;
		x->rightChild_ = y->leftChild_;

		if (y->leftChild_ != nil_)
			y->leftChild_->parent_ = x;

		y->parent_ = x->parent_;

		if (x->parent_ == nil_)
			root_ = y;
		else if (x == x->parent_->leftChild_)
			x->parent_->leftChild_ = y;
		else
			x->parent_->rightChild_ = y;

		y->leftChild_ = x;
		x->parent_ = y;

	}

	template<class T>
	void RBT<T>::rightRotation(std::shared_ptr<RBTreeNode<T>> y)
	{
		auto x = y->leftChild_;
		y->leftChild_ = x->rightChild_;

		if (x->rightChild_ != nil_)
			x->rightChild_->parent_ = y;

		x->parent_ = y->parent_;

		if (y->parent_ == nil_)
			root_ = x;
		else if (y == y->parent_->rightChild_)
			y->parent_->rightChild_ = y;
		else
			y->parent_->leftChild_ = y;
		x->rightChild_ = y;
		y->parent_ = x;
	}

	template<class T>
	void RBT<T>::insert_modifyColor(std::shared_ptr<RBTreeNode<T>> current_node)
	{
		while (current_node->parent_->color_ == RBTreeNode<T>::RED)
		{
			// current node is left child
			if (current_node->parent_ == current_node->parent_->parent_->leftChild_)
			{
				auto uncle = current_node->parent_->parent_->rightChild_;
				//case 1: if uncle is red
				if (uncle->color_ == RBTreeNode<T>::RED)
				{
					current_node->parent_->color_ = RBTreeNode<T>::BLACK;
					uncle->color_ = RBTreeNode<T>::BLACK;
					current_node->parent_->parent_->color_ = RBTreeNode<T>::RED;
					current_node = current_node->parent_->parent_;
				}
				else //case 2&3: uncle is black
				{
					//case 2
					if (current_node == current_node->parent_->rightChild_)
					{
						current_node = current_node->parent_;
						leftRotation(current_node);
					}
					//case 3
					current_node->parent_->color_ = RBTreeNode<T>::BLACK;
					current_node->parent_->parent_->color_ = RBTreeNode<T>::RED;
					rightRotation(current_node->parent_->parent_);
				}
			}
			// current node is right child
			else
			{
				auto uncle = current_node->parent_->parent_->leftChild_;

				if (uncle->color_ == RBTreeNode<T>::RED)
				{
					current_node->parent_->color_ = RBTreeNode<T>::BLACK;
					uncle->color_ = RBTreeNode<T>::BLACK;
					current_node->parent_->parent_->color_ = RBTreeNode<T>::RED;
					current_node = current_node->parent_->parent_;
				}
				else
				{
					//case 2
					if (current_node == current_node->parent_->leftChild_)
					{
						current_node = current_node->parent_;
						rightRotation(current_node);
					}
					//case 3
					current_node->parent_->color_ = RBTreeNode<T>::BLACK;
					current_node->parent_->parent_->color_ = RBTreeNode<T>::RED;
					leftRotation(current_node->parent_->parent_);
				}
			}
		}
		root_->color_ = RBTreeNode<T>::BLACK;
	}

	template<class T>
	void RBT<T>::delete_modifyColor(std::shared_ptr<RBTreeNode<T>> current_node)
	{
		while (current_node != root_ && current_node->color_ == RBTreeNode<T>::BLACK)
		{
			// current node is left child
			if (current_node == current_node->parent_->leftChild_)
			{
				auto sibling = current_node->parent_->rightChild_;
				if (sibling->color_ == RBTreeNode<T>::RED) {
					sibling->color_ = 1;
					current_node->parent_->color_ = 0;
					leftRotation(current_node->parent_);
					sibling = current_node->parent_->rightChild_;
				}

				if (sibling->rightChild_->color_ == RBTreeNode<T>::BLACK && sibling->rightChild_->color_ == RBTreeNode<T>::BLACK) {
					sibling->color_ = 0;
					current_node = current_node->parent_;
				}
				else
				{
					if (sibling->rightChild_->color_ == RBTreeNode<T>::BLACK) {
						sibling->leftChild_->color_ = RBTreeNode<T>::RED;
						sibling->color_ = RBTreeNode<T>::RED;
						rightRotation(sibling);
						sibling = current_node->parent_->rightChild_;
					}
	
					sibling->color_ = current_node->parent_->color_;
					current_node->parent_->color_ = RBTreeNode<T>::BLACK;
					sibling->rightChild_->color_ = RBTreeNode<T>::BLACK;
					leftRotation(current_node->parent_);
					current_node = root_;     
				}
			}
			// current node is right child
			else
			{
				auto sibling = current_node->parent_->leftChild_;
				if (sibling->color_ == RBTreeNode<T>::RED) {
					sibling->color_ = RBTreeNode<T>::BLACK;
					current_node->parent_->color_ = RBTreeNode<T>::RED;
					rightRotation(current_node->parent_);
					sibling = current_node->parent_->leftChild_;
				}

				if (sibling->leftChild_->color_ == RBTreeNode<T>::BLACK && sibling->rightChild_->color_ == RBTreeNode<T>::BLACK) {
					sibling->color_ = RBTreeNode<T>::BLACK;
					current_node = current_node->parent_;             
				}
				else
				{
					if (sibling->leftChild_->color_ == RBTreeNode<T>::BLACK) {
						sibling->rightChild_->color_ = RBTreeNode<T>::BLACK;
						sibling->color_ = RBTreeNode<T>::RED;
						leftRotation(sibling);
						sibling = current_node->parent_->leftChild_;
					}

					sibling->color_ = current_node->parent_->color_;
					current_node->parent_->color_ = RBTreeNode<T>::BLACK;
					sibling->leftChild_->color_ = RBTreeNode<T>::BLACK;
					rightRotation(current_node->parent_);
					current_node = root_;     
				}
			}
		}
		current_node->color_ = RBTreeNode<T>::BLACK;
	}

	template<class T>
	std::shared_ptr<RBTreeNode<T>> RBT<T>::successor(std::shared_ptr<RBTreeNode<T>> current_node)
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

	template<class T>
	std::shared_ptr<RBTreeNode<T>> RBT<T>::leftMost(std::shared_ptr<RBTreeNode<T>> current_node)
	{
		while (current_node->leftChild_ != nullptr)
		{
			current_node = current_node->leftChild_;
		}
		return current_node;
	}

}


#endif // !RED_BLACK_TREE_H

