#pragma once

namespace las {

	template<typename Key, typename Value> class Map;

	template<typename Key, typename Value>
	class TreeNode {
		friend class Map<Key, Value>;
	public:
		TreeNode() 
			: m_value(), m_key(), m_red(true), m_parent(nullptr), m_left(nullptr), m_right(nullptr)
		{

		}
		TreeNode(const Value& value, const Key& key, TreeNode<Key,Value>* parent = nullptr, TreeNode<Key, Value>* left = nullptr, TreeNode<Key, Value>* right = nullptr)
			: m_value(value), m_key(key),m_parent(parent),m_left(left),m_right(right),m_red(true)
		{}

		const Key& getKey() const {
			return m_key;
		}

		Value& getValue() {
			return m_value;
		}

		const Value& getValue()const {
			return m_value;
		}

		void setValue(const Value& value) {
			m_value = value;
		}

		bool isRed() {
			return m_red;
		}

		TreeNode<Key, Value>* getParent() {
			return m_parent;
		}

		TreeNode<Key, Value>* getLeft() {
			return m_left;
		}

		TreeNode<Key, Value>* getRight() {
			return m_right;
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

	private:
		Value m_value;
		Key m_key;
		bool m_red;
		TreeNode<Key, Value>* m_parent;
		TreeNode<Key, Value>* m_left;
		TreeNode<Key, Value>* m_right;

	};

	template<typename Key, typename Value>
	class Map {
		typedef TreeNode<Key, Value> Node;
	public:
		Map() {

		}

		bool insert(Key key, Value value = value()) {
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
					
				}
			}
		return success;
		}

		void erase(Key key) {
			//TODO erase key from tree
		}

		Value& operator[](Key key) {
			//TODO access value by key
			//If key doesn't exist, insert key
			return Value();
		}

		const Value& operator[](Key key) const{
			//TODO access const value by key. 
			//If key doesn't exist, throw exception
			return Value();
		}

		bool exists(Key key) const {
			//TODO check if key is in map
			return false;
		}

	private:
		Node* m_root;

		void rebalance() {
			//TODO rebalance tree
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
						grandparent->m_left == pivot;
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