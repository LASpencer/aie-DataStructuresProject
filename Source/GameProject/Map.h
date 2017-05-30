#pragma once
#include "stdafx.h"
#include "Defines.h"
#include "Array.h"

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

		// Value constructor
		TreeNode(const K& key, const V& value, TreeNode<K,V>* parent = nullptr, TreeNode<K, V>* left = nullptr, TreeNode<K, V>* right = nullptr)
			: m_key(key), m_value(value), m_parent(parent),m_left(left),m_right(right),m_red(true)
		{}

		/**Copy constructor
		* Copies key and value from other node, but not its place in the tree*/
		TreeNode(const TreeNode<K, V>& other) : m_key(other.m_key), m_value(other.m_value), m_red(true),m_parent(nullptr),m_left(nullptr),m_right(nullptr) {

		}
		
		/**Copy assignment
		* Copies key and value from other node, but remains in same place in the tree*/
		TreeNode<K, V>& operator=(const TreeNode<K, V>&other) {
			m_key = other.m_key;
			m_value = other.m_value;
			return *this;
		}

		/** Move constructor
		* Move key and value from other node, but each keeps its place in the tree*/
		TreeNode(TreeNode<K,V>&& other)
			: m_value(), m_key(), m_red(true), m_parent(nullptr), m_left(nullptr), m_right(nullptr)
		{
			m_value = std::move(other.m_value);
			m_key = std::move(other.m_key);
		}

		/** Move assignment
		* Move key and value from other node, but each keeps its place in the tree*/
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

		/** Gets the other child of this node's parent
		* @return pointer to the other child of this node's parent, or nullptr if parent is nullptr*/
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

		/** Finds the root node of this node's tree
		* @return pointer to root node*/
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
				// If left child exists, predecessor is greatest key among left descendents
				return m_left->getSubtreeMax();
			}
			else {
				// Else predecessor is first ancestor less than this node
				TreeNode<K, V>* node = this;
				TreeNode<K, V>* parent = m_parent;
				// Traverse up tree until parent less than its child
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
				// If right child exists, successor is lowest key among right descendents
				return m_right->getSubtreeMin();
			}
			else {
				// Else successor is first ancestor greater than its node
				TreeNode<K, V>* node = this;
				TreeNode<K, V>* parent = m_parent;
				// Traverse up tree until parent greater than its child
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
				// Traverse down tree until node without lower child found
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
				// Traverse down tree until node without greater child found
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

		// Creates array containing copies of all key-value pairs in tree
		Array<std::pair<K, V>> flattenSubtree() {
			Array<std::pair<K, V>> subtree{ std::make_pair(m_key, m_value) };
			if (m_left != nullptr) {
				Array<std::pair<K, V>> left = m_left->flattenSubtree();
				subtree.insert(subtree.end(), left.begin(), left.end());
			}
			if (m_right != nullptr) {
				Array<std::pair<K, V>> right = m_right->flattenSubtree();
				subtree.insert(subtree.end(), right.begin(), right.end());
			}
			return subtree;
		}

		// Equality operator returns true if key and value are equal
		bool operator==(const TreeNode<K, V>&other) const {
			return (other.m_key == m_key) && (other.m_value == m_value);
		}

		/**Counts total black nodes between this and null leaves
		* @return number of black nodes to all leaves, including the leaves, or 0 if unbalanced*/
		size_t blackNodesToLeaf() const{
			size_t left, right, result;
			if (m_left == nullptr) {
				// If null leaf, count it as 1 black node
				left = 1;
			} else {
				// If not null, recursively call for child
				left = m_left->blackNodesToLeaf();
			}
			// Do same for right child
			if (m_right == nullptr) {
				right = 1;
			} else {
				right = m_right->blackNodesToLeaf();
			}
			if (left == right) {
				// If both have same result, subtree is sufficiently balanced
				result = left;
				if (!m_red) {
					// If this node is black, add 1 to total
					++result;
				}
			} else {
				// If different results, subtree is unbalanced, so return 0
				result = 0;
			}
			return result;
		}

		/** Tests if any red nodes have red children in subtree
		* @return true if any adjacent red nodes in subtree*/
		bool adjacentRedNodes() const{
			bool left, right;
			if (m_left == nullptr) {
				// null node counts as black
				left = false;
			} else {
				// Recursively call for left node, and check if both this and left are red
				left = (m_red && m_left->m_red) || m_left->adjacentRedNodes();
			}
			// Do same with right node
			if (m_right == nullptr) {
				right = false;
			} else {
				right = (m_red && m_right->m_red) || m_right->adjacentRedNodes();
			}
			// If adjacent red nodes found on either child, return true
			return left || right;
		}

		// Returns total number of nodes in subtree
		size_t subtreeSize() const {
			size_t size = 1;
			if (m_left != nullptr) {
				size += m_left->subtreeSize();
			}
			if (m_right != nullptr) {
				size += m_right->subtreeSize();
			}
			return size;
		}

	private:
		K m_key;
		V m_value;
		bool m_red;					// Whether the node is considered red or black when rebalancing the tree
		TreeNode<K, V>* m_parent;	// Parent of this node
		TreeNode<K, V>* m_left;		// Child with key less than this node's key
		TreeNode<K, V>* m_right;	// Child with key greater than this node's key

	};

	template<typename K, typename V> class MapIter;
	template<typename K, typename V> class MapConstIter;

	template<typename K, typename V>
	class Map {
		typedef TreeNode<K, V> Node;
	public:

		// Define iterators and iterator traits
		friend class MapIter<K, V>;
		friend class MapConstIter<K,V>;
		typedef MapIter<K, V> iterator;
		typedef MapConstIter<K, V> const_iterator;
		//TODO document mapiter,begin,end

		Map() : m_root(nullptr)
		{

		}

		/** Initializer List Constructor
		* @param list Initializer list containing key, value pairs to insert*/
		Map(std::initializer_list<std::pair<K, V>> list) :m_root(nullptr)
		{
			for (std::pair<K,V> element:list) {
				insert(element.first, element.second);
			}
		}

		// Copy constructor
		Map(const Map<K, V>& other) {
			m_root = new Node();
			m_root->copySubtree(*(other.m_root));
		}

		// Copy assignment
		Map<K, V>& operator=(const Map<K, V>& other) {
			m_root->copySubtree(*(other.m_root));
			return *this;
		}

		// Move constructor
		Map(Map<K, V>&& other) {
			m_root = other.m_root;
			other.m_root = nullptr;
		}

		// Move assignment
		Map<K, V>& operator=(Map<K, V>&&other) {
			delete m_root;
			m_root = other.m_root;
			other.m_root = nullptr;
			return *this;
		}

		// Destructor
		~Map() {
			if (m_root != nullptr) {
				delete m_root;
			}
		}

		iterator begin() {
			return iterator(m_root->getSubtreeMin(), this);
		}

		const_iterator begin() const {
			return const_iterator(m_root->getSubtreeMin(), this);
		}

		iterator end() {
			return iterator(nullptr, this);
		}

		const_iterator end() const {
			return const_iterator(nullptr, this);
		}

		/** Inserts new key value pair into map
		* @param key inserted key
		* @param value inserted value
		* @return true if insertion successful, false if key already exists*/
		bool insert(K key, V value = V()) {
			Node* newNode = new Node(key, value);
			bool success = true;
			if (m_root == nullptr) {
				// If no root, insert node as root
				m_root = newNode;
				m_root->m_red = false;		// Set root colour to black
			}
			else {
				// Find null leaf to insert new node
				Node* place = m_root;
				while (place != nullptr) {
					if (newNode->m_key < place->m_key) {
						// If new key less than current place in tree, move left
						Node* leftNode = place->getLeft();
						if (leftNode == nullptr) {
							//insert newNode into leaf
							newNode->m_parent = place;
							place->m_left = newNode;
							place = nullptr;
						}
						else {
							place = leftNode;
						}
					}
					else if (place->m_key < newNode->m_key) {
						// If new key greater than current place in tree, move right
						Node* rightNode = place->getRight();
						if (rightNode == nullptr) {
							//insert newNode into leaf
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
					rebalanceInsert(newNode);
				}
			}
		return success;
		}

		/** Erase key-value pair from map
		* @param key Key to erase from map
		* @return iterator following erased element*/
		iterator erase(K key) {
			return erase(iterator(findNode(key), this));
		}

		/** Erase key-value pair from map
		* @param pos Iterator referencing element to erase from map
		* @return iterator following erased element*/
		iterator erase(iterator pos) {
			Node* node = pos.m_node;
			iterator next;
			if (node != nullptr) {
				if (node->m_right != nullptr) {
					//Copy successor, then delete that node instead
					Node* successor = node->m_right->getSubtreeMin();
					*node = *successor;
					next = iterator(node, this);	//Next iterator points to node, as successor copied there
					node = successor;
				}
				else {
					next = iterator(node->getSuccessor(), this);	//Next iterator points to successor's node
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
					// Rebalance until double black resolved
					assert(child == m_root || sibling != nullptr);
					if (child == m_root) {
						// Root double black converts to single black
						doubleBlack = false;
					}
					else if (!sibling->m_red) {
						//If sibling is black, check nephew colour
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
				return next;
			} else {
				return end();
			}
		}

		/**Subscript operator
		* @param key Key to element accessed
		* @return reference to element*/
		V& operator[](K key) {
			// Find node, and last node searched in case node doesn't exist
			std::pair<Node*, Node*> nodeAndParent = findNodeAndParent(key);
			Node* node = nodeAndParent.first;
			if (node == nullptr) {
				// If key doesn't exist, insert node with key and default value
				node = new Node(key, V());
				if (m_root == nullptr) {
					// If emptry tree, new node is root
					node->m_red = false;
					m_root = node;
				}
				else {
					// Set node's parent as last node searched
					Node* parent = nodeAndParent.second;
					node->m_parent = parent;
					//  Set node as correct child of parent
					if (node->m_key < parent->m_key) {
						parent->m_left = node;
					}
					else {
						parent->m_right = node;
					}
					// Rebalance after insertion
					rebalanceInsert(node);
				}
			}
			return node->m_value;
		}

		/**Subscript operator
		* @param key Key to element accessed
		* @return const reference to element*/
		const V& operator[](K key) const{
			Node* node = findNode(key);
			// If key doesn't exist, throw exception
			if (node == nullptr) {
				throw std::out_of_range("key does not exist in map");
			}
			return node->m_value;
		}

		/** Access element in map
		* @param key Key to element accessed
		* @return reference to element*/
		V& at(K key) {
			Node* node = findNode(key);
			// If element doesn't exist, throw exception
			if (node == nullptr) {
				throw std::out_of_range("key does not exist in map");
			}
			return node->m_value;
		}

		/** Access element in map
		* @param key Key to element accessed
		* @return constant reference to element*/
		const V& at(K key) const {
			Node* node = findNode(key);
			// If element doesn't exist, throw exception
			if (node == nullptr) {
				throw std::out_of_range("key does not exist in map");
			}
			return node->m_value;
		}

		/** Test if key exists in map
		* @param key to check for
		* @return true if key exists in map*/
		bool exists(K key) const {
			return findNode(key) != nullptr;
		}

		/** Test if tree is balances
		* @return true if tree follows rules for red-black tree*/
		bool isBalanced() const{
			if (m_root != nullptr) {
				return !m_root->isRed()&& m_root->blackNodesToLeaf() != 0 && !m_root->adjacentRedNodes();
			} else {
				// Empty tree is balanced
				return true;
			}
		}

		/** Creates array containing all elements of the map
		* @return array*/
		Array<std::pair<K, V>> flattenMap() {
			if (m_root != nullptr) {
				return m_root->flattenSubtree();
			}
			else {
				return Array<std::pair<K, V>>();
			}
		}

		/** Gets number of elements in map
		* @return number of elements in map*/
		size_t size() {
			size_t mapSize = 0;
			if (m_root != nullptr) {
				mapSize = m_root->subtreeSize();
			}
			return mapSize;
		}

		/** Checks if map has no elements
		* @return true if no elements in map*/
		bool empty() {
			return m_root == nullptr;
		}

#ifdef TESTING_TREE_NODES
		Node* getRoot() {
			return m_root;
		}
#endif

	private:
		Node* m_root;

		/** Finds node with specified key
		* @param key Key of node required
		* @return Pointer to node with specified key, or nullptr if not found*/
		Node* findNode(K key) const {
			return findNodeAndParent(key).first;
		}

		/** Finds node with specified key and its parent
		* @param key Key of node required
		* @return Pair of pointer to node with specified key and its parent, or nullptr and pointer to last node searched if not found*/
		std::pair<Node*,Node*> findNodeAndParent(K key) const {
			Node* node = m_root;
			Node* parent = nullptr;
			while (node != nullptr && node->getKey() != key) {
				// If search not over, set parent to node being checked
				parent = node;
				// Set node to child depending on key ordering
				if (node->getKey() < key) {
					node = node->getRight();
				}
				else if (node->getKey() > key) {
					node = node->getLeft();
				}
			}
			return std::make_pair(node, parent);
		}

		/** Resolve any imbalance caused by pivot
		* @param pivot node which might cause imbalance */
		void rebalanceInsert(Node* pivot) {
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
					assert(grandparent != nullptr);		// Root cannot be red
					Node* uncle;
					bool parentLeft;		// Is parent left child of grandparent
					if (grandparent->getLeft() == parent) {
						uncle = grandparent->getRight();
						parentLeft = true;
					}
					else {
						uncle = grandparent->getLeft();
						parentLeft = false;
					}
					if (uncle != nullptr && uncle->isRed()) {
						// If uncle red, push parent and uncle redness to grandparent
						parent->m_red = false;
						uncle->m_red = false;
						grandparent->m_red = true;
						// Recursively call on grandparent
						rebalanceInsert(grandparent);
					}
					else {
						bool pivotLeft = parent->getLeft() == pivot;	// Is this left child of parent
						if (pivotLeft != parentLeft) {
							// Left Right, Right Left case
							// Rotate pivot up to grandparent's position
							rotate(pivot);
							rotate(pivot);
							// Move redness down to former grandparent
							pivot->m_red = false;
							grandparent->m_red = true;
						} else {
							// Left Left, Right Right case
							// Rotate parent up
							rotate(parent);
							// Move parent's redness down to former grandparent
							grandparent->m_red = true;
							parent->m_red = false;
						}
						// Tree is now balanced
					}
				}
			}
		}

		/** Rotates pivot into parent's position
		* @param pivot Node to rotate into higher position*/
		void rotate(Node* pivot) {

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
					// Pivot becomes its parent's parent
					parent->m_parent = pivot;
					pivot->m_right = parent;
					// Pivot's right child is now left child of parent
					parent->m_left = temp;
					if (temp != nullptr) {
						temp->m_parent = parent;
					}
				}
				else {
					// Rotate to left
					Node* temp = pivot->m_left;
					// Pivot becomes its parent's parent
					parent->m_parent = pivot;
					pivot->m_left = parent;
					// Pivot's left child is now right child of parent
					parent->m_right = temp;
					if (temp != nullptr) {
						temp->m_parent = parent;
					}
				}
				// Pivot's new parent is its former grandparent
				pivot->m_parent = grandparent;
				if (grandparent != nullptr) {
					if (grandparent->m_right == parent) {
						grandparent->m_right = pivot;
					}
					else {
						grandparent->m_left = pivot;
					}
				}
				// If parent was root, pivot is now root
				if (m_root == parent) {
					m_root = pivot;
				}
			}
		}
	};

	//TODO test iterators work

	// Iterator for map classes
	template <typename K, typename V>
	class MapIter : public std::iterator<std::bidirectional_iterator_tag, std::pair<const K&,V&>> {
	public:
		friend class Map<K, V>;

		MapIter() : m_node(nullptr), m_map(nullptr)
		{

		}

		/**Value Constructor
		* @param node TreeNode containing referenced value
		* @param map Map being iterated over*/
		MapIter(TreeNode<K,V>* node, Map<K,V>* map) : m_node(node), m_map(map) 
		{
		}

		value_type operator*() {
			if (m_node == nullptr) {
				throw std::out_of_range("End iterator not dereferenceable");
			}
			return std::pair<const K&, V&>(m_node->getKey(), m_node->getValue());
		}

		std::unique_ptr<value_type> operator->() {
			if (m_node == nullptr) {
				throw std::out_of_range("End iterator not dereferenceable");
			}
			return std::make_unique<std::pair<const K&, V&>>(m_node->getKey(), m_node->getValue());
		}

		bool operator==(const MapIter<K, V>&other) const {
			return m_node == other.m_node && m_map == other.m_map;
		}

		bool operator!=(const MapIter<K, V>&other) const {
			return !(*this == other);
		}

		operator MapConstIter<K, V>() {
			return MapConstIter<K, V>(m_node, m_map);
		}

		MapIter<K, V>& operator++(){
			if (m_node != nullptr) {
				m_node = m_node->getSuccessor();
			}
			return *this;
		}

		MapIter<K, V> operator++(int) {
			MapIter<K, V> old(*this);
			if (m_node != nullptr) {
				m_node = m_node->getSuccessor();
			}
			return old;
		}

		MapIter<K, V>& operator--() {
			if (m_node != nullptr) {
				TreeNode<K, V>* prev = m_node->getPredecessor();
				if (prev != nullptr) {
					m_node = prev;
				}
			} else {
				m_node = m_map->m_root->getSubtreeMax();
			}
			return *this;
		}

		MapIter<K, V> operator--(int) {
			MapIter<K, V> old(*this);
			if (m_node != nullptr) {
				TreeNode<K, V>* prev = m_node->getPredecessor();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {
				m_node = m_map->m_root->getSubtreeMax();
			}
			return old;
		}

	private:
		Map<K,V>* m_map;
		TreeNode<K,V>* m_node;
	};

	// Constant Iterator for map classes
	template <typename K, typename V>
	class MapConstIter : public std::iterator<std::bidirectional_iterator_tag, std::pair<const K&, const V&>> {
	public:
		friend class Map<K, V>;

		MapConstIter() : m_node(nullptr), m_map(nullptr)
		{

		}

		/**Value Constructor
		* @param node TreeNode containing referenced value
		* @param map Map being iterated over*/
		MapConstIter(TreeNode<K, V>* node, Map<K, V>* map) : m_node(node), m_map(map)
		{
		}

		value_type operator*() {
			if (m_node == nullptr) {
				throw std::out_of_range("End iterator not dereferenceable");
			}
			return std::pair<const K&, const V&>(m_node->getKey(), m_node->getValue());
		}

		std::unique_ptr<value_type> operator->() {
			if (m_node == nullptr) {
				throw std::out_of_range("End iterator not dereferenceable");
			}
			return std::make_unique<std::pair<const K&, const V&>>(m_node->getKey(), m_node->getValue());
		}

		bool operator==(const MapIter<K, V>&other) const {
			return m_node == other.m_node && m_map == other.m_map;
		}

		bool operator!=(const MapIter<K, V>&other) const {
			return !(*this == other);
		}

		operator MapConstIter<K, V>() {
			return MapConstIter<K, V>(m_node, m_map);
		}

		MapConstIter<K, V>& operator++() {
			if (m_node != nullptr) {
				m_node = m_node->getSuccessor();
			}
			return *this;
		}

		MapConstIter<K, V> operator++(int) {
			MapConstIter<K, V> old(*this);
			if (m_node != nullptr) {
				m_node = m_node->getSuccessor();
			}
			return old;
		}

		MapConstIter<K, V>& operator--() {
			if (m_node != nullptr) {
				TreeNode<K, V>* prev = m_node->getPredecessor();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {
				m_node = m_map->m_root->getSubtreeMax();
			}
			return *this;
		}

		MapConstIter<K, V> operator--(int) {
			MapConstIter<K, V> old(*this);
			if (m_node != nullptr) {
				TreeNode<K, V>* prev = m_node->getPredecessor();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {
				m_node = m_map->m_root->getSubtreeMax();
			}
			return old;
		}

	private:
		Map<K, V>* m_map;
		TreeNode<K, V>* m_node;
	};
}