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

		//TODO copy ctor, copy assign operator
		//TODO dtor

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
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

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
			//TODO use empty()
			if (m_front == nullptr) {
				throw std::out_of_range("Empty list has no front");
			}
			return m_front->value;
		}

		T& back() {
			//TODO use empty()
			if (m_back == nullptr) {
				throw std::out_of_range("Empty list has no back");
			}
			return m_back->value;
		}

		//TODO const front, back

		void push_front(const T& value) {
			//TODO add to start of list
			ListNode<T>* newElement = new ListNode<T>(value, nullptr, m_front);
			if (m_front == nullptr) {
				assert(m_back == nullptr);
				m_back = newElement;
			}
			else {
				m_front->setPrevious(newElement);
			}
			m_front = newElement;
		}

		void push_back(const T& value) {
			//TODO add to end of list
			ListNode<T>* newElement = new ListNode<T>(value,m_back);
			if (m_back == nullptr) {
				assert(m_front == nullptr);
				m_front = newElement;
			}
			else {
				m_back->setNext(newElement);
			}
			m_back = newElement;
		}

		T pop_front() {
			//TODO remove front and return value
			if (m_front == nullptr) {
				throw std::out_of_range("Empty list has no front");
			}
			T value = m_front->value;
			ListNode<T>* newFront = m_front->getNext();
			m_front->setNext(nullptr);
			if (newFront == nullptr) {
				m_back = nullptr;
			}
			else {
				newFront->setPrevious(nullptr);
			}
			delete m_front;
			m_front = newFront;
			return value;
		}

		T pop_back() {
			//TODO remove back and return value
			if (m_back == nullptr) {
				throw std::out_of_range("Empty list has no back");
			}
			T value = m_back->value;
			ListNode<T>* newBack = m_back->getPrevious();
			m_back->setPrevious(nullptr);
			if (newBack == nullptr) {
				m_front = nullptr;
			}
			else {
				newBack->setNext(nullptr);
			}
			delete m_back;
			m_back = newBack;
			return value;
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

		//TODO operator==

	private:
		ListNode<T>* m_front;
		ListNode<T>* m_back;
	};

	//TODO comment ListIter
	template <typename T>
	class ListIter : public std::iterator<std::bidirectional_iterator_tag, T> {
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