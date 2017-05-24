#pragma once

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

		const K& getKey() const {
			return m_key;
		}

		V& getValue() {
			return m_value;
		}

		const V& getValue()const {
			return m_value;
		}

		void setValue(const V& value) {
			m_value = value;
		}

		bool isRed() {
			return m_red;
		}

		TreeNode<K, V>* getParent() {
			return m_parent;
		}

		TreeNode<K, V>* getLeft() {
			return m_left;
		}

		TreeNode<K, V>* getRight() {
			return m_right;
		}

		/** getPredecessor
		* @return Pointer to node with next lowest key in tree, or nullptr if this is lowest*/
		TreeNode<K, V>* getPredecessor() {
			if (m_left != nullptr) {
				return m_left->getSubtreeMax();
			} else {
				TreeNode<K, V>* node = this;
				TreeNode<K, V>* parent = m_parent;
				while (parent != nullptr && node == parent->m_left) {
					node = parent;
					parent = parent->m_parent;
				}
				return parent;
			}
		}

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

		// Returns node with maximum key in subtree with this as root
		TreeNode<K, V>* getSubtreeMax() {
			TreeNode<K, V>* node = this;
			TreeNode<K, V>* max;
			while (node != nullptr) {
				min = node;
				node = node->m_right;
			}
			return max;
		}

		size_t blackNodesToLeaf() {
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

		bool adjacentRedNodes() {
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
		}

		V& operator[](K key) {
			//TODO access value by key
			//If key doesn't exist, insert key
			return V();
		}

		const V& operator[](K key) const{
			//TODO access const value by key. 
			//If key doesn't exist, throw exception
			return V();
		}

		bool exists(K key) const {
			//TODO check if key is in map
			return false;
		}

		bool isBalanced() {
			if (m_root != nullptr) {
				return !m_root->isRed()&& m_root->blackNodesToLeaf() != 0 && !m_root->adjacentRedNodes();
			} else {
				// Empty tree is balanced
				return true;
			}
		}

		Node* getRoot() {
			return m_root;
		}

	private:
		Node* m_root;

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
				}
				else {
					// Rotate to left
					Node* temp = pivot->m_left;
					parent->m_parent = pivot;
					pivot->m_left = parent;
					parent->m_right = temp;
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