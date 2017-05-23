#pragma once

namespace las {
	template<typename Key, typename Value>
	class TreeNode {
	public:
		TreeNode() 
			: value(), m_key(), m_red(true), m_parent(nullptr), m_left(nullptr), m_right(nullptr)
		{

		}
		Value value;
	private:
		Key m_key;
		bool m_red;
		TreeNode<Key, Value>* m_parent;
		TreeNode<Key, Value>* m_left;
		TreeNode<Key, Value>* m_right;
	};

	template<typename Key, typename Value>
	class Map {
	public:
		Map() {

		}
	private:
		TreeNode<Key, Value>* m_root;
	};
}