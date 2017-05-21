#pragma once
#include <initializer_list>
#include <iterator>
#include <type_traits>

namespace las {

	// Node holding elements of double linked list
	template <typename T>
	class ListNode {
	public:

		ListNode() : value(T()), m_previous(nullptr), m_next(nullptr)
		{}
		
		/** Value constructor
		* @param a_value value contained in the node
		* @param previous pointer to list node before this
		* @param next pointer to list node following this */
		ListNode(T a_value, ListNode<T>* previous = nullptr, ListNode<T>* next = nullptr) :
			value(a_value), m_previous(previous), m_next(next)
		{}

		ListNode<T>* getPrevious() {
			return m_previous;
		}

		ListNode<T>* getNext() {
			return m_next;
		}

		void setPrevious(ListNode<T>* previous) {
			//TODO check validity of previous
			m_previous = previous;
		}

		void setNext(ListNode<T>* next) {
			//TODO check validity of next
			m_next = next;
		}

		T value;
	private:
		ListNode<T>* m_previous;
		ListNode<T>* m_next;
	};

	template <typename T> class ListIter;
	//TODO ListConstIter template class

	//TODO comment list
	template <typename T>
	class List {
	public:

		friend class ListIter<T>;
		typedef ListIter<T> iterator;
		//TODO typedef ListConstIter<T> const_iterator;
		typedef iterator::difference_type difference_type;
		typedef iterator::size_type size_type;
		typedef iterator::value_type value_type;
		typedef iterator::pointer pointer;
		typedef iterator::reference reference;

		List() : m_front(nullptr), m_back(nullptr)
		{
		}

		//TODO initializer list

		//TODO range ctor

		//TODO fill ctor

		//TODO copy ctor, copy assignment operator

		~List() 
		{
		}

		iterator begin() {
			return ListIter(m_front, this);
		}

		iterator end() {
			return ListIter(nullptr, this);
		}

		//TODO const begin, end

		T& front() {
			//TODO assert/exception if m_front == nullptr
			return m_front->value;
		}

		T& back() {
			//TODO assert/exception if m_back == nullptr
			return m_back->value;
		}

		//TODO const front, back

		void push_front(const T& value) {
			//TODO add to start of list
		}

		void push_back(const T& value) {
			//TODO add to end of list
		}

		T pop_front() {
			//TODO remove front and return value
		}

		T pop_back() {
			//TODO remove back and return value
		}

		iterator insert(iterator position, const T& value) {
			//TODO insert value before position
			return iterator();
		}

		void insert(iterator position, size_type count, const T& value) {
			//TODO fill before position with count elements of value
		}

		template <typename Iter,
			typename = typename std::enable_if<std::is_same<std::iterator_traits<Iter>::value_type, T>::value, Iter >::type> //Substitution failure if Iter is not input iterator containing T
			void insert(iterator position, Iter first, Iter last) {
			//TODO insert before position from range
		}

		iterator erase(iterator position) {
			//TODO erase element
			return iterator();
		}

		iterator erase(iterator first, iterator last) {
			//TODO erase range
			return iterator();
		}

		void remove(const T& value) {
			//TODO remove all with value
		}

		//TODO maybe: remove(predicate)

		void clear() {
			//TODO remove all elements
		}

		size_t size() {
			//TODO count through nodes? Or keep a value?
			return size_t();
		}

		bool empty() {
			return m_front == nullptr;
		}

	private:
		ListNode<T>* m_front;
		ListNode<T>* m_back;
	};

	//TODO comment ListIter
	template <typename T>
	class ListIter : public iterator<std::bidirectional_iterator_tag, T> {
	public:

		ListIter<T>() : m_node(nullptr), m_list(nullptr)
		{}

		ListIter<T>(ListNode<T>* node, List<T>* list) :
			m_node(node), m_list(list)
		{}

		ListIter<T>(ListIter<T>&other) : m_node(other.m_node), m_list(other.m_list)
		{
		}

		~ListIter<T>()
		{}

		ListIter<T>& operator=(ListIter<T>&other) {
			m_node = other.m_node;
			m_list = other.m_list;
			return *this;
		}

		T& operator*() {
			return m_node->value;
		}

		//TODO check this is right
		T* operator->() {
			return &(m_node->value);
		}

		bool operator==(ListIter<T>&other) {
			//HACK what if a node can belong to multiple lists?
			return m_node == other.m_node;
		}

		bool operator!=(ListIter<T>&other) {
			return m_node != other.m_node;
		}

		ListIter<T>& operator++() {
			if (m_node != nullptr) {
				ListNode<T>* next = m_node->getNext();
			}
			return *this;
		}

		ListIter<T> operator++(int) {
			ListIter<T> old(*this);
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return old;
		}

		ListIter<T>& operator--() {
			if (m_node != nullptr) {
				ListIter<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			} else {	// If nullptr, reference final element of list
				m_node = m_list->m_back;
			}
			return *this;
		}

		ListIter<T> operator--(int) {
			ListIter<T> old(*this);
			if (m_node != nullptr) {
				ListIter<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {	// If nullptr, reference final element of list
				m_node = m_list->m_back;
			}
			return old;
		}


	private:
		ListNode<T>* m_node;
		List<T>* m_list;
	};
}