#pragma once
#include <initializer_list>
#include "Defines.h"

namespace las {

	template<typename K, typename V> class Map;

	template<typename K, typename V>
	class TreeNode {
		friend class Map<K, V>;
	public:
		TreeNode() 
			: m_value(), m_key(), m_red(true), m_parent(nullptr), m_left(nullptr), m_right(nullptr)
		{

		}

		TreeNode(const K& key, const V& value, TreeNode<K,V>* parent = nullptr, TreeNode<K, V>* left = nullptr, TreeNode<K, V>* right = nullptr)
			: m_value(value), m_key(key),m_parent(parent),m_left(left),m_right(right),m_red(true)
		{}

		//TODO copy, move
		TreeNode(const TreeNode<K, V>& other) : m_key(other.m_key), m_value(other.m_value), m_red(true),m_parent(nullptr),m_left(nullptr),m_right(nullptr) {

		}
		
		//copies key and value, but stays in same place in tree
		TreeNode<K, V>& operator=(const TreeNode<K, V>&other) {
			m_key = other.m_key;
			m_value = other.m_value;
			return *this;
		}

		// Moves key and value, but each node stays in same place
		TreeNode(TreeNode<K,V>&& other)
			: m_value(), m_key(), m_red(true), m_parent(nullptr), m_left(nullptr), m_right(nullptr)
		{
			m_value = std::move(other.m_value);
			m_key = std::move(other.m_key);
		}

		TreeNode<K, V>& operator=(TreeNode<K, V>&&other) {
			m_value = std::move(other.m_value);
			m_key = std::move(other.m_key);
			return *this;
		}

		// Remove references to self from children and parent
		~TreeNode() {
			// Delete all descendents
			if (m_left != nullptr) {
				m_left->m_parent = nullptr;
				delete m_left;
			}
			if (m_right != nullptr) {
				m_right->m_parent = nullptr;
				delete m_right;
			}
			// Remove self from parent
			if (m_parent != nullptr) {
				if (m_parent->m_left == this) {
					m_parent->m_left = nullptr;
				}
				else if (m_parent->m_right == this) {
					m_parent->m_right = nullptr;
				}
			}
		}

		// Destroys all descendents of this node
		void destroySubtree() {
			if (m_left != nullptr) {
				delete m_left;
			}
			if (m_right != nullptr) {
				delete m_right;
			}
		}

		// Copies other node and creates new subtree identical to its subtree
		void copySubtree(const TreeNode<K, V>& other) {
			// Destroy current subtree
			destroySubtree();
			m_key = other.m_key;
			m_value = other.m_value;
			m_red = other.m_red;
			if (other.m_left != nullptr) {
				m_left = new TreeNode<K, V>();
				m_left->m_parent = this;
				m_left->copySubtree(*(other.m_left));
			}
			if (other.m_right != nullptr) {
				m_right = new TreeNode<K, V>();
				m_right->m_parent = this;
				m_right->copySubtree(*(other.m_right));
			}
		}

		const K& getKey() const {
			return m_key;
		}

		V& getValue() {
			return m_value;
		}

		//const V& getValue()const {
		//	return m_value;
		//}

		void setValue(const V& value) {
			m_value = value;
		}

		bool isRed()const {
			return m_red;
		}

		TreeNode<K, V>* getParent() {
			return m_parent;
		}

		TreeNode<K, V>* getSibling() {
			if (m_parent != nullptr) {
				if (m_parent->m_left == this) {
					return m_parent->m_right;
				}
				else {
					return m_parent->m_left;
				}
			}
			else {
				return nullptr;
			}
		}
		//const TreeNode<K, V>* getParent() const {
		//	return m_parent;
		//}

		TreeNode<K, V>* getLeft() {
			return m_left;
		}

		//const TreeNode<K, V> getLeft() const {
		//	return m_left;
		//}

		TreeNode<K, V>* getRight() {
			return m_right;
		}

		//const TreeNode<K, V>* getRight() const {
		//	return m_right;
		//}

		TreeNode<K, V>* getRoot() {
			if (m_parent == nullptr) {
				return this;
			}
			else {
				return m_parent->getRoot();
			}
		}

		/** getPredecessor
		* @return Pointer to node with next lowest key in tree, or nullptr if this is lowest*/
		TreeNode<K, V>* getPredecessor() {
			if (m_left != nullptr) {
				return m_left->getSubtreeMax();
			}
			else {
				TreeNode<K, V>* node = this;
				TreeNode<K, V>* parent = m_parent;
				while (parent != nullptr && node == parent->m_left) {
					node = parent;
					parent = parent->m_parent;
				}
				return parent;
			}
		}

		//const TreeNode<K, V>* getPredecessor() const {
		//	if (m_left != nullptr) {
		//		return m_left->getSubtreeMax();
		//	}
		//	else {
		//		const TreeNode<K, V>* node = this;
		//		const TreeNode<K, V>* parent = m_parent;
		//		while (parent != nullptr && node == parent->m_left) {
		//			node = parent;
		//			parent = parent->m_parent;
		//		}
		//		return parent;
		//	}
		//}

		/** getSuccessor
		* @return Pointer to node with next greatest key in tree, or nullptr if this is greatest*/
		TreeNode<K, V>* getSuccessor() {
			if (m_right != nullptr) {
				return m_right->getSubtreeMin();
			}
			else {
				TreeNode<K, V>* node = this;
				TreeNode<K, V>* parent = m_parent;
				while (parent != nullptr && node == parent->m_right) {
					node = parent;
					parent = parent->m_parent;
				}
				return parent;
			}
		}

		//const TreeNode<K, V> getSuccessor() const{
		//	if (m_right != nullptr) {
		//		return m_right->getSubtreeMin();
		//	}
		//	else {
		//		const TreeNode<K, V>* node = this;
		//		const TreeNode<K, V>* parent = m_parent;
		//		while (parent != nullptr && node == parent->m_right) {
		//			node = parent;
		//			parent = parent->m_parent;
		//		}
		//		return parent;
		//	}
		//}

		// Returns node with minimum key in subtree with this as root
		TreeNode<K, V>* getSubtreeMin() {
			TreeNode<K, V>* node = this;
			TreeNode<K, V>* min;
			while (node != nullptr) {
				min = node;
				node = node->m_left;
			}
			return min;
		}

		//const TreeNode<K, V>* getSubtreeMin() const {
		//	const TreeNode<K, V>* node = this;
		//	const TreeNode<K, V>* min;
		//	while (node != nullptr) {
		//		min = node;
		//		node = node->m_left;
		//	}
		//	return min;
		//}


		// Returns node with maximum key in subtree with this as root
		TreeNode<K, V>* getSubtreeMax() {
			TreeNode<K, V>* node = this;
			TreeNode<K, V>* max;
			while (node != nullptr) {
				max = node;
				node = node->m_right;
			}
			return max;
		}

		// Returns node with maximum key in subtree with this as root
		//const TreeNode<K, V>* getSubtreeMax() const {
		//	const TreeNode<K, V>* node = this;
		//	const TreeNode<K, V>* max;
		//	while (node != nullptr) {
		//		max = node;
		//		node = node->m_right;
		//	}
		//	return max;
		//}

		// Equality operator returns true if key and value are equal
		bool operator==(const TreeNode<K, V>&other) const {
			return (other.m_key == m_key) && (other.m_value == m_value);
		}

		size_t blackNodesToLeaf() const{
			size_t left, right, result;
			if (m_left == nullptr) {
				left = 1;
			} else {
				left = m_left->blackNodesToLeaf();
			}
			if (m_right == nullptr) {
				right = 1;
			} else {
				right = m_right->blackNodesToLeaf();
			}
			if (left == right) {
				result = left;
				if (!m_red) {
					++result;
				}
			} else {
				result = 0;
			}
			return result;
		}

		bool adjacentRedNodes() const{
			bool left, right;
			if (m_left == nullptr) {
				left = false;
			} else {
				left = (m_red && m_left->m_red) || m_left->adjacentRedNodes();
			}
			if (m_right == nullptr) {
				right = false;
			} else {
				right = (m_red && m_right->m_red) || m_right->adjacentRedNodes();
			}
			return left || right;
		}

	private:
		V m_value;
		K m_key;
		bool m_red;
		TreeNode<K, V>* m_parent;
		TreeNode<K, V>* m_left;
		TreeNode<K, V>* m_right;

	};

	template<typename K, typename V>
	class Map {
		typedef TreeNode<K, V> Node;
	public:
		Map() : m_root(nullptr)
		{

		}

		Map(std::initializer_list<std::pair<K, V>> list) :m_root(nullptr)
		{
			for (std::pair<K,V> element:list) {
				insert(element.first, element.second);
			}
		}

		//TODO copy, move ctor
		Map(const Map<K, V>& other) {
			m_root = new Node();
			m_root->copySubtree(*(other.m_root));
		}

		Map<K, V>& operator=(const Map<K, V>& other) {
			m_root->copySubtree(*(other.m_root));
			return *this;
		}

		Map(Map<K, V>&& other) {
			m_root = other.m_root;
			other.m_root = nullptr;
		}

		Map<K, V>& operator=(Map<K, V>&&other) {
			delete m_root;
			m_root = other.m_root;
			other.m_root = nullptr;
			return *this;
		}

		//TODO dtor
		~Map() {
			if (m_root != nullptr) {
				m_root->destroySubtree();
				delete m_root;
			}
		}

		bool insert(K key, V value = V()) {
			//TODO add new tree node for key containing value
			//Returns true if inserted, false if not (because key already exists)
			Node* newNode = new Node(key, value);
			bool success = true;
			if (m_root == nullptr) {
				m_root = newNode;
				m_root->m_red = false;
			}
			else {
				Node* place = m_root;
				while (place != nullptr) {
					if (newNode->m_key < place->m_key) {
						Node* leftNode = place->getLeft();
						if (leftNode == nullptr) {
							//insert newNode as left of place
							newNode->m_parent = place;
							place->m_left = newNode;
							place = nullptr;
						}
						else {
							place = leftNode;
						}
					}
					else if (place->m_key < newNode->m_key) {
						Node* rightNode = place->getRight();
						if (rightNode == nullptr) {
							//insert newNode as right of place
							newNode->m_parent = place;
							place->m_right = newNode;
							place = nullptr;
						}
						else {
							place = rightNode;
						}
					}
					else {
						// Key collision
						success = false;
						delete newNode;
						break;
					}
				}
				if (success) {
					//TODO check tree balanced, and rebalance if not
					rebalanceInsert(newNode);
				}
			}
		return success;
		}

		void erase(K key) {
			//TODO erase key from tree
			Node* node = findNode(key);
			if (node != nullptr) {
				if (node->m_right != nullptr) {
					//Copy successor, then delete that node instead
					Node* successor = node->m_right->getSubtreeMin();
					*node = *successor;
					node = successor;
				}
				// Node now has at most one child
				Node* child = node->m_right;
				if (child == nullptr) {
					child = node->m_left;
				}
				// Check if deletion would unbalance tree
				bool doubleBlack = !(node->m_red) && (child == nullptr || !(child->m_red));
				Node* parent = node->m_parent;
				Node* sibling = node->getSibling();
				// Set child to black and reparent it
				if (child != nullptr) {
					child->m_red = false;
					child->m_parent = parent;
				}
				if (parent != nullptr) {
					if (parent->m_left == node) {
						node->m_parent->m_left = child;
					}
					else {
						parent->m_right = child;
					}
				}
				else {
					// If no parent, node must be root so set child as new root
					assert(node == m_root);
					m_root = child;
				}
				// Remove node's references and delete it
				node->m_parent = nullptr;
				node->m_left = nullptr;
				node->m_right = nullptr;
				delete node;
				while (doubleBlack) {
					//TODO rebalance while double black
					assert(child == m_root || sibling != nullptr);
					if (child == m_root) {
						// Root double black converts to single black
						doubleBlack = false;
					}
					else if (!sibling->m_red) {
						//If sibling is black, check nephew colour
						//HACK refactor to avoid redundant if statements
						Node* nephew = nullptr;
						if ( sibling->m_left != nullptr && sibling->m_left->m_red) {
							nephew = sibling->m_left;
						}
						else if (sibling->m_right != nullptr && sibling->m_right->m_red) {
							nephew = sibling->m_right;
						}
						if (nephew != nullptr) {
							// If red nephew found, rotate and recolour based on left-left or right-left case
							bool siblingLeft = (parent->m_left == sibling);
							bool nephewLeft = (sibling->m_left == nephew);
							bool bothRed = (sibling->m_left != nullptr && sibling->m_right != nullptr && sibling->m_left->m_red && sibling->m_right->m_red);
							if(siblingLeft == nephewLeft){
								// Left-left/Right-Right
								// Rotate sibling up
								rotate(sibling);
								// Nephew is now black
								nephew->m_red = false;
								//If parent was red, move redness to sibling
								if (parent->m_red) {
									sibling->m_red = true;
									parent->m_red = false;
								}
							} else if (bothRed) {
								// Left-Left/Right-Right, if both red and wrong nephew picked earlier
								// Set correct nephew to black
								if (siblingLeft) {
									sibling->m_left->m_red = false;
								}
								else {
									sibling->m_right->m_red = false;
								}
								// Rotate sibling up
								rotate(sibling);
								//If parent was red, move redness to sibling
								if (parent->m_red) {
									sibling->m_red = true;
									parent->m_red = false;
								}
							} else {
								// Rotate nephew to create left-left/right-right case
								// Then rotate again and recolour to resolve double blackness
								rotate(nephew);
								rotate(nephew);
								if (parent->m_red) {
									// If parent was red, move redness to nephew
									nephew->m_red = true;
									parent->m_red = false;
								}
								else {
									//If parent was black, nephew becomes black
									nephew->m_red = false;
								}
							}
							// Double black resolved
							doubleBlack = false;
						}
						else {
							//If sibling is black and has 2 black children, move black up to parent
							sibling->m_red = true;
							if (parent->m_red) {
								// If parent is red, make it black resolving double black
								parent->m_red = false;
								doubleBlack = false;
							}
							else {
								// If parent is black, it is now the double black node
								child = parent;
								parent = child->m_parent;
								sibling = child->getSibling();
								if (parent == nullptr) {
									// If new parent is nullptr, child is at root and double black is resolved
									doubleBlack = false;
								}
							}
						}
					}
					else {
						//Sibling is red
						//rotate sibling up
						rotate(sibling);
						// Sibling is now black and parent is red
						sibling->m_red = false;
						parent->m_red = true;
						// Get pointer to new sibling
						if (parent->m_left == child) {
							sibling = parent->m_right;
						} else {
							sibling = parent->m_left;
						}
					}
				}
			}
		}

		V& operator[](K key) {
			//TODO access value by key
			//If key doesn't exist, insert key
			Node* node = findNode(key);
			if (node == nullptr) {
				/*HACK super inefficient. 
				Maybe have findNode return the node's parent too*/
				insert(key);
				node = findNode(key);
			}
			return node->m_value;
		}

		const V& operator[](K key) const{
			//TODO access const value by key. 
			Node* node = findNode(key);
			if (node == nullptr) {
				throw std::out_of_range("key does not exist in map");
			}
			return node->m_value;
		}

		bool exists(K key) const {
			//TODO check if key is in map
			return findNode(key) != nullptr;
		}

		bool isBalanced() const{
			if (m_root != nullptr) {
				return !m_root->isRed()&& m_root->blackNodesToLeaf() != 0 && !m_root->adjacentRedNodes();
			} else {
				// Empty tree is balanced
				return true;
			}
		}

#ifdef TESTING_TREE_NODES
		Node* getRoot() {
			return m_root;
		}
#endif

	private:
		Node* m_root;

		Node* findNode(K key) const {
			Node* node = m_root;
			while (node != nullptr && node->getKey() != key) {
				if (node->getKey() < key) {
					node = node->getRight();
				}
				else if (node->getKey() > key) {
					node = node->getLeft();
				}
			}
			return node;
		}

		void rebalanceInsert(Node* pivot) {
			//TODO rebalance tree
			//TODO test insert, write isBalanced method to test tree follows rules after insertion/deletion
			assert(pivot != nullptr);
			assert(pivot->isRed());
			Node* parent = pivot->getParent();
			if (parent == nullptr) {
				// Turn black at root
				pivot->m_red = false;
			} else {
				// If parent is red, tree not balanced
				if (pivot->getParent()->isRed()) {
					Node* grandparent = pivot->getParent()->getParent();
					assert(grandparent != nullptr);
					Node* uncle;
					bool parentLeft;
					if (grandparent->getLeft() == parent) {
						uncle = grandparent->getRight();
						parentLeft = true;
					}
					else {
						uncle = grandparent->getLeft();
						parentLeft = false;
					}
					if (uncle != nullptr && uncle->isRed()) {
						// Make parent and uncle black
						parent->m_red = false;
						uncle->m_red = false;
						// Make grandparent red
						grandparent->m_red = true;
						// Call this function on grandparent
						rebalanceInsert(grandparent);
					}
					else {
						bool pivotLeft = parent->getLeft() == pivot;
						if (pivotLeft != parentLeft) {
							// Left Right, Right Left case
							// Rotate pivot up to grandparent's position
							rotate(pivot);
							rotate(pivot);
							// Pivot is now back, grandparent is now red
							pivot->m_red = false;
							grandparent->m_red = true;
						} else {
							// Left Left, Right Right case
							// Rotate parent up
							rotate(parent);
							// Parent is now black, grandparent is now red
							grandparent->m_red = true;
							parent->m_red = false;
						}
						// Tree is now balanced
					}
				}
			}
		}

		void rotate(Node* pivot) {
			//TODO rotate
			//TODO test rotate
			// Check if pivot has parent
			// If so, rotate
			// Check if pivot is new root
			assert(pivot != nullptr);
			Node* parent = pivot->m_parent;
			if (parent != nullptr) {
				Node* grandparent = parent->m_parent;
				if (pivot->m_key < parent->m_key) {
					// Rotate to right
					Node* temp = pivot->m_right;
					parent->m_parent = pivot;
					pivot->m_right = parent;
					parent->m_left = temp;
					if (temp != nullptr) {
						temp->m_parent = parent;
					}
				}
				else {
					// Rotate to left
					Node* temp = pivot->m_left;
					parent->m_parent = pivot;
					pivot->m_left = parent;
					parent->m_right = temp;
					if (temp != nullptr) {
						temp->m_parent = parent;
					}
				}
				pivot->m_parent = grandparent;
				//TODO if grandparent not nullptr, set pivot as approprite child of grandparent
				if (grandparent != nullptr) {
					if (grandparent->m_right == parent) {
						grandparent->m_right = pivot;
					}
					else {
						grandparent->m_left = pivot;
					}
				}
				//TODO if parent was root, pivot is now root
				if (m_root == parent) {
					m_root = pivot;
				}
			}
		}
	};
}