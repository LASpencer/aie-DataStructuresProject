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

		/**Copy constructor
		* Copies value of other ListNode
		* @param other listNode of same type*/
		ListNode(const ListNode<T>& other) : m_previous(nullptr), m_next(nullptr), value(other.value)
		{}

		/**Copy assignment
		* Copies value of other ListNode, while keeping same position in list
		* @param other listNode of same type
		* @return this ListNode*/
		ListNode<T>& operator=(const ListNode<T>& other) {
			value = other.value;
			return *this;
		}

		/** Move Constructor
		* Moves value from other ListNode, and replaces it in its list
		* @param other listNode of same type*/
		ListNode(ListNode<T>&& other) : m_previous(other.m_previous), m_next(other.m_next)
		{
			value = std::move(other.value);
			if (m_previous != nullptr) {
				m_previous->setNext(this);
			}
			if (m_next != nullptr) {
				m_next->setPrevious(this);
			}
			other.setPrevious(nullptr);
			other.setNext(nullptr);
		}

		/** Move Assignment
		* Moves value from other ListNode, and replaces it in its list
		* @param other listNode of same type
		* @return this ListNode*/
		ListNode<T>& operator=(ListNode<T>&& other) {
			//Remove self from current list, putting nodes on either side together
			if (m_previous != nullptr) {
				m_previous->m_next = m_next;
			}
			if (m_next != nullptr) {
				m_next->m_previous = m_previous;
			}
			// Move self into other list
			m_previous = other.m_previous;
			m_next = other.m_next;
			if (m_previous != nullptr) {
				m_previous->m_next = this;
				other.m_previous = nullptr;
			}
			if (m_next != nullptr) {
				m_next->m_previous = this;
				other.m_next = nullptr;
			}
			// move value
			value = std::move(other.value);
			return *this;
		}

		/**Destructor
		* Ensures nodes on either side have valid references*/
		~ListNode() {
			// Leave nodes on either side with valid references
			if (m_previous != nullptr) {
				m_previous->m_next = m_next;
			}
			if (m_next != nullptr) {
				m_next->m_previous = m_previous;
			}
		}

		ListNode<T>* getPrevious() {
			return m_previous;
		}

		ListNode<T>* getNext() {
			return m_next;
		}

		void setPrevious(ListNode<T>* previous) {
			m_previous = previous;
		}

		void setNext(ListNode<T>* next) {
			m_next = next;
		}

		T value;
	private:
		ListNode<T>* m_previous;
		ListNode<T>* m_next;
	};

	template <typename T> class ListIter;
	template <typename T> class ListConstIter;

	// A templated class for double linked lists
	template <typename T>
	class List {
	public:
		
		// Define iterators and iterator traits
		friend class ListIter<T>;
		friend class ListConstIter<T>;
		typedef ListIter<T> iterator;
		typedef ListConstIter<T> const_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;


		List() : m_front(nullptr), m_back(nullptr)
		{
		}

		/** Initializer List Constructor
		* @param iList initializer list containing values for elements*/
		List(std::initializer_list<T> iList) : m_front(nullptr), m_back(nullptr)
		{
			for (T element : iList) {
				push_back(element);
			}
		}

		/** Range Constructor
		* Constructs List from elements in given range
		* @param first iterator to first element in range
		* @param last iterator to end of range*/
		template <typename Iter,
			typename = typename std::enable_if<std::is_same<std::iterator_traits<Iter>::value_type, T>::value, Iter >::type> //Substitution failure if Iter is not input iterator containing T
			List(Iter first, Iter last) : m_front(nullptr), m_back(nullptr)
		{
			if (first != last) {
				m_front = new ListNode<T>(*first);
				m_back = m_front;
				for (Iter it = ++first; it != last; ++it) {
					ListNode<T>* newNode = new ListNode<T>(*it, m_front);
					m_back->setNext(newNode);
					m_back = newNode;
				}
			}
		}

		// Copy Constructor
		List(const List<T>& other) : m_front(nullptr), m_back(nullptr)
		{
			insert(end(), other.begin(), other.end());
		}

		// Copy Assignment 
		List<T>& operator=(const List<T>& other) {
			// Copy values into current nodes
			ListNode<T>* node = m_front;
			for (const_iterator it = other.begin(); it != other.end(); ++it) {
				// Copy into existing nodes until end reached
				if (node != nullptr) {
					node->value = *it;
					node = node->getNext();
				}
				else {
					// If no more nodes, push value back
					push_back(*it);
				}

			}
			// If too many nodes, delete unneeded nodes
			while (node != nullptr) {
				ListNode<T>* next = node->getNext();
				delete node;
				node = next;
			}
			return *this;
		}

		// Move Constructor
		List(List<T>&& other) :  m_front(other.m_front),m_back(other.m_back)
		{
			other.m_front = nullptr;
			other.m_back = nullptr;

		}

		// Move Assignment
		List<T>& operator=(List<T>&& other) {
			// Destroy current nodes
			ListNode<T>* node = m_front;
			while (node != nullptr) {
				ListNode<T>* next = node->getNext();
				delete node;
				node = next;
			}
			// Move front and back from other
			m_front = other.m_front;
			other.m_front = nullptr;
			m_back = other.m_back;
			other.m_back = nullptr;
			return *this;
		}

		/** Destructor
		* Destroys all nodes in list*/
		~List() 
		{
			// traverse list deleting each node
			ListNode<T>* node = m_front;
			while (node != nullptr) {
				ListNode<T>* next = node->getNext();
				delete node;
				node = next;
			}
		}


		/**begin
		* @return iterator to first element of list*/
		iterator begin() {
			return iterator(m_front, this);
		}

		/**end
		* @return iterator past final element of list*/
		iterator end() {
			return iterator(nullptr, this);
		}

		/**begin
		* @return constant iterator to first element of list*/
		const_iterator begin() const {
			//HACK
			const_iterator begin;
			begin.m_node = m_front;
			begin.m_list = this;
			return begin;
		}
		
		/**end
		* @return constant iterator past end of list*/
		const_iterator end() const {
			//return const_iterator(nullptr, this);
			//HACK 
			const_iterator end;
			end.m_list = this;
			return end;
		}

		/**front
		* @return reference to first element of list*/
		T& front() {
			if (m_front == nullptr) {
				throw std::out_of_range("Empty list has no front");
			}
			return m_front->value;
		}

		/**back
		* @return reference to last element of list*/
		T& back() {
			if (m_back == nullptr) {
				throw std::out_of_range("Empty list has no back");
			}
			return m_back->value;
		}

		/**front
		* @return constant reference to first element of list*/
		const T& front() const {
			if (m_front == nullptr) {
				throw std::out_of_range("Empty list has no front");
			}
			return m_front->value;
		}

		/**back
		* @return constant reference to last element of list*/
		const T& back() const {
			if (m_back == nullptr) {
				throw std::out_of_range("Empty list has no back");
			}
			return m_back->value;
		}

		/**push_front
		* Inserts new element to front of list
		* @param value element to insert*/
		void push_front(const T& value) {
			ListNode<T>* newElement = new ListNode<T>(value, nullptr, m_front);
			if (m_front == nullptr) {
				// If list is empty, this is also the back
				assert(m_back == nullptr);
				m_back = newElement;
			}
			else {
				m_front->setPrevious(newElement);
			}
			m_front = newElement;
		}

		/**push_back
		* Inserts new element to end of list
		* @param value element to insert*/
		void push_back(const T& value) {
			ListNode<T>* newElement = new ListNode<T>(value,m_back);
			if (m_back == nullptr) {
				// If list is empty, this is also the front
				assert(m_front == nullptr);
				m_front = newElement;
			}
			else {
				m_back->setNext(newElement);
			}
			m_back = newElement;
		}

		/**pop_front
		* Removes first element from list
		* @return value of removed element*/
		T pop_front() {
			if (m_front == nullptr) {
				throw std::out_of_range("Empty list has no front");
			}
			T value = m_front->value;
			ListNode<T>* newFront = m_front->getNext();
			m_front->setNext(nullptr);
			if (newFront == nullptr) {
				// If end was reached, list is empty
				m_back = nullptr;
			}
			else {
				newFront->setPrevious(nullptr);
			}
			delete m_front;
			m_front = newFront;
			return value;
		}

		/**pop_back
		* Removes last element from list
		* @return value of removed element*/
		T pop_back() {
			if (m_back == nullptr) {
				throw std::out_of_range("Empty list has no back");
			}
			T value = m_back->value;
			ListNode<T>* newBack = m_back->getPrevious();
			m_back->setPrevious(nullptr);
			if (newBack == nullptr) {
				// If start was reached, list is empty
				m_front = nullptr;
			}
			else {
				newBack->setNext(nullptr);
			}
			delete m_back;
			m_back = newBack;
			return value;
		}

		/**insert
		* Inserts new element into list
		* @param position iterator to element before which new element is to be inserted
		* @param value element to insert
		* @return iterator to position following inserted element*/
		void insert(iterator position, const T& value) {
			if (position.m_list != this) {
				throw std::invalid_argument("position is not an iterator of this list");
			}
			ListNode<T>* node = position.m_node;
			if (node == nullptr) {
				push_back(value);
			}
			else if (node == m_front) {
				push_front(value);
			} else{
				ListNode<T>* newElement = new ListNode<T>(value, node->getPrevious(), node);
				if (newElement->getPrevious() != nullptr) {
					newElement->getPrevious()->setNext(newElement);
				}
				node->setPrevious(newElement);
			}
		}

		/**insert
		* Inserts multiple elements into list
		* @param position iterator to element before which new element is to be inserted
		* @param count number of copies of value to insert
		* @param value element to insert*/
		void insert(iterator position, size_t count, const T& value) {
			if (position.m_list != this) {
				throw std::invalid_argument("position is not an iterator of this list");
			}
			if (count != 0) {
				// Create LinkNodes for new elements
				ListNode<T>* head = new ListNode<T>(value);
				ListNode<T>* tail = head;
				for (size_t i = 1; i < count; ++i) {
					ListNode<T>* nextNode = new ListNode<T>(value, tail);
					tail->setNext(nextNode);
					tail = nextNode;
				}
				// Link new nodes with current nodes
				ListNode<T>* node = position.m_node;
				if (node == nullptr) {
					// Insert at end
					if (m_back != nullptr) {
						m_back->setNext(head);
					} else {
						// If empty list, front is head
						m_front = head;
					}
					head->setPrevious(m_back);
					m_back = tail;
				}
				else if (node == m_front) {
					// Insert at front
					m_front->setPrevious(tail);
					tail->setNext(m_front);
					m_front = head;
				}
				else {
					head->setPrevious(node->getPrevious());
					node->getPrevious()->setNext(head);
					tail->setNext(node);
					node->setPrevious(tail);
				}
			}
		}


		/** insert
		* Inserts elements from range
		* @param position iterator to element before which new element is to be inserted
		* @param first iterator to first element in range
		* @param last iterator to end of range*/
		template <typename Iter,
			typename = typename std::enable_if<std::is_same<std::iterator_traits<Iter>::value_type, T>::value, Iter >::type> //Substitution failure if Iter is not input iterator containing T
			void insert(iterator position, Iter first, Iter last) {
			if (position.m_list != this) {
				throw std::invalid_argument("position is not an iterator of this list");
			}
			if (first != last) {
				// Create LinkNodes for elements
				ListNode<T>* head = new ListNode<T>(*first);
				ListNode<T>* tail = head;
				for (Iter it = ++first; it != last; ++it) {
					ListNode<T>* nextNode = new ListNode<T>(*it, tail);
					tail->setNext(nextNode);
					tail = nextNode;
				}
				// Link new nodes with current nodes
				ListNode<T>* node = position.m_node;
				if (node == nullptr) {
					// Insert at end
					if (m_back != nullptr) {
						m_back->setNext(head);
					}
					else {
						// If empty list, front is head
						m_front = head;
					}
					head->setPrevious(m_back);
					m_back = tail;
				}
				else if (node == m_front) {
					// Insert at front
					m_front->setPrevious(tail);
					tail->setNext(m_front);
					m_front = head;
				}
				else {
					head->setPrevious(node->getPrevious());
					node->getPrevious()->setNext(head);
					tail->setNext(node);
					node->setPrevious(tail);
				}
			}
		}

		//TODO sort list

		/**erase
		* Remove element from list and destroys it
		* @param position element to be removed
		* @return iterator following erased element*/
		iterator erase(iterator position) {
			if (position.m_list != this) {
				throw std::invalid_argument("position is not an iterator of this list");
			}
			if (position.m_node == nullptr) {
				throw std::out_of_range("cannot erase past end of list");
			}
			if (position.m_node == m_front) {
				m_front = m_front->getNext();
			}
			if (position.m_node == m_back) {
				m_back = m_back->getPrevious();
			}
			iterator next = position;
			++next;
			delete position.m_node;
			return next;
		}

		/**erase
		* Removes and destroys all elements within range
		* @param first start of range
		* @param last element past end of range
		* @return iterator following erased elements*/
		iterator erase(iterator first, iterator last) {
			if (first.m_list != this || last.m_list != this) {
				throw std::invalid_argument("first and last must both be iterators of this list");
			}
			if (first.m_node == nullptr) {
				throw std::out_of_range("first cannot be end iterator");
			}
			// Check range is valid
			for (iterator it = first; it != last; ++it) {
				if (it == end()) {
					throw std::out_of_range("last could not be reached by incrementing first");
				}
			}
			//Check if erasing front
			if (first.m_node == m_front) {
				m_front = last.m_node;
			}
			//Check if erasing end
			if (last == end()) {
					m_back = first.m_node->getPrevious();
			}
			// Delete nodes from first until last is reached
			ListNode<T>* node = first.m_node;
			while (node != last.m_node) {
				ListNode<T>* next = node->getNext();
				delete node;
				node = next;
			}
			return last;
		}

		/**remove
		* Remove all elements matching value from list
		* @param value value to remove from list*/
		void remove(const T& value) {
			ListNode<T>* node = m_front;
			while (node != nullptr) {
				ListNode<T>* next = node->getNext();
				if (node->value == value) {
					// Check if node is front or back
					if (node == m_front) {
						m_front = next;
					}
					if (node == m_back) {
						m_back = node->getPrevious();
					}
					delete node;
				}
				node = next;
			}
		}

		//TODO maybe: remove_if(predicate)

		/** clear
		* Destroy all elements of list*/
		void clear() {
			// traverse list deleting each node
			ListNode<T>* node = m_front;
			while (node != nullptr) {
				ListNode<T>* next = node->getNext();
				delete node;
				node = next;
			}
			m_front = nullptr;
			m_back = nullptr;
		}

		/**size
		* @return number of elements in list*/
		size_t size() const {
			size_t count = 0;
			for (const_iterator it = begin(); it != end(); ++it) {
				++count;
			}
			return count;
		}

		/**empty
		* @return true if no elements in list, false otherwise*/
		bool empty() const {
			return m_front == nullptr;
		}

		/** Equality operator
		* Tests if both lists have same values in all elements
		* @param other other list of same type
		* @return true if all elements equal, false otherwise*/
		bool operator==(const List<T>& other) const {
			const_iterator thisList = begin();
			const_iterator otherList = other.begin();
			bool equal = true;
			while (thisList != end() && otherList != other.end() && equal == true) {
				equal = (*thisList == *otherList);
				++thisList;
				++otherList;
			}
			if (thisList != end() || otherList != other.end()) {
				equal = false;
			}
			return equal;
		}


		bool operator!=(List<T> other) {
			return !(*this == other);
		}

	private:
		ListNode<T>* m_front;
		ListNode<T>* m_back;
	};

	// Iterator for List classes
	template <typename T>
	class ListIter : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		friend class List<T>;

		ListIter() : m_node(nullptr), m_list(nullptr)
		{}

		/** Value constructor
		* @param node ListNode containing referenced value
		* @param list List being iterated over*/
		ListIter(ListNode<T>* node, List<T>* list) :
			m_node(node), m_list(list)
		{}

		// Copy constructor
		ListIter(ListIter<T>&other) : m_node(other.m_node), m_list(other.m_list)
		{
		}

		~ListIter()
		{}

		// Copy assignment
		ListIter<T>& operator=(ListIter<T>&other) {
			m_node = other.m_node;
			m_list = other.m_list;
			return *this;
		}

		/**Indirection operator
		* @return reference to value*/
		T& operator*() {
			if (m_node == nullptr) {
				throw std::out_of_range("End iterator not dereferenceable");
			}
			return m_node->value;
		}

		/**Member access operator
		* */
		T* operator->() {
			if (m_node == nullptr) {
				throw std::out_of_range("End iterator not dereferenceable");
			}
			return &(m_node->value);
		}

		bool operator==(const ListIter<T>&other) const {
			bool equal = m_node == other.m_node && m_list == other.m_list;
			return equal;
		}

		bool operator!=(const ListIter<T>&other) const {
			return !(*this == other);
		}

		//TODO fix this conversion
		operator ListConstIter<T>() {
			return ListConstIter<T>(m_node, m_list);
		}

		/** pre increment operator
		* Increments to next element, unless this is end iterator
		* @return this iterator, after being incremented*/
		ListIter<T>& operator++() {
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return *this;
		}

		/** post increment operator
		* Increments to next element, unless this is end iterator
		* @return copy of this iterator before being incremented*/
		ListIter<T> operator++(int) {
			ListIter<T> old(*this);
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return old;
		}

		/** addition operator
		* Increments multiple times
		* @param count times to increment iterator
		* @return copy of this iterator, incremented multiple times*/
		ListIter<T> operator+(size_t count) {
			ListIter<T> result(*this);
			for (size_t i = 0; i < count; ++i) {
				++result;
			}
			return result;
		}

		/** addition assigment
		* Increments multiple times
		* @param count times to increment iterator
		* @return copy of this iterator*/
		ListIter<T>& operator+=(size_t count) {
			for (size_t i = 0; i < count; ++i) {
				++(*this);
			}
			return *this;
		}

		/** pre decrement operator
		* Decrements to previous element, unless this is start of list.
		* @return this iterator, after being decremented*/
		ListIter<T>& operator--() {
			if (m_node != nullptr) {
				ListNode<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			} else {	// If end iterator, reference final element of list
				m_node = m_list->m_back;
			}
			return *this;
		}

		/** post decrement operator
		* Decrements to previous element, unless this is start of list.
		* @return copy of this iterator before being decremented*/
		ListIter<T> operator--(int) {
			ListIter<T> old(*this);
			if (m_node != nullptr) {
				ListNode<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {	// If end iterator, reference final element of list
				m_node = m_list->m_back;
			}
			return old;
		}

		/** subtraction operator
		* @param count times to decrement iterator
		* @return copy of this iterator, decremented multiple times*/
		ListIter<T> operator-(size_t count) {
			ListIter<T> result(*this);
			for (size_t i = 0; i < count; ++i) {
				--result;
			}
			return result;
		}

		/** subtraction assigment
		* Decrements multiple times
		* @param count times to decrement iterator
		* @return copy of this iterator*/
		ListIter<T>& operator-=(size_t count) {
			for (size_t i = 0; i < count; ++i) {
				--(*this);
			}
			return *this;
		}

	private:
		ListNode<T>* m_node;		// ListNode containing element, if nullptr this is end iterator
		List<T>* m_list;			// List being iterated over
	};

	// Constant Iterator for List classes
	template <typename T>
	class ListConstIter : public std::iterator<std::bidirectional_iterator_tag, T, ptrdiff_t,const T*, const T&> {
	public:
		friend class List<T>;

		ListConstIter() : m_node(nullptr), m_list(nullptr)
		{}

		/** Value constructor
		* @param node ListNode containing referenced value
		* @param list List being iterated over*/
		ListConstIter(ListNode<T>* node, List<T>* list) :
			m_node(node), m_list(list)
		{}

		ListConstIter(ListConstIter<T>&other) : m_node(other.m_node), m_list(other.m_list)
		{}

		~ListConstIter()
		{}

		ListConstIter<T>& operator=(ListConstIter<T>&other) {
			m_node = other.m_node;
			m_list = other.m_list;
			return *this;
		}

		/**Indirection operator
		* @return const reference to value*/
		const T& operator*() const {
			return m_node->value;
		}

		//TODO check this is right const usage
		const T* operator->() const {
			return &(m_node->value);
		}

		bool operator==(const ListConstIter<T>&other) const {
			bool equal = m_node == other.m_node && m_list == other.m_list;
			return equal;
		}

		bool operator!=(const ListConstIter<T>&other) const {
			return !(*this == other);
		}

		/** pre increment operator
		* Increments to next element, unless this is end iterator
		* @return this iterator, after being incremented*/
		ListConstIter<T>& operator++() {
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return *this;
		}

		/** post increment operator
		* Increments to next element, unless this is end iterator
		* @return copy of this iterator before being incremented*/
		ListConstIter<T> operator++(int) {
			ListConstIter<T> old(*this);
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return old;
		}

		/** addition operator
		* Increments multiple times
		* @param count times to increment iterator
		* @return this iterator after being repeatedly incremented*/
		ListConstIter<T> operator+(size_t count) {
			ListConstIter<T> result(*this);
			for (size_t i = 0; i < count; ++i) {
				++result;
			}
			return result;
		}

		/** addition assigment
		* Increments multiple times
		* @param count times to increment iterator
		* @return copy of this iterator*/
		ListConstIter<T>& operator+=(size_t count) {
			for (size_t i = 0; i < count; ++i) {
				++(*this);
			}
			return *this;
		}

		/** pre decrement operator
		* Decrements to previous element, unless this is start of list.
		* @return this iterator, after being decremented*/
		ListConstIter<T>& operator--() {
			if (m_node != nullptr) {
				ListNode<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {	// If end iterator, reference final element of list
				m_node = m_list->m_back;
			}
			return *this;
		}

		/** post decrement operator
		* Decrements to previous element, unless this is start of list.
		* @return copy of this iterator before being decremented*/
		ListConstIter<T> operator--(int) {
			ListConstIter<T> old(*this);
			if (m_node != nullptr) {
				ListNode<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {	// If end iterator, reference final element of list
				m_node = m_list->m_back;
			}
			return old;
		}

		/** subtraction operator
		* @param count times to decrement iterator
		* @return copy of this iterator, decremented multiple times*/
		ListConstIter<T> operator-(size_t count) {
			ListConstIter<T> result(*this);
			for (size_t i = 0; i < count; ++i) {
				--result;
			}
			return result;
		}

		/** subtraction assigment
		* Decrements multiple times
		* @param count times to decrement iterator
		* @return copy of this iterator*/
		ListConstIter<T>& operator-=(size_t count) {
			for (size_t i = 0; i < count; ++i) {
				--(*this);
			}
			return *this;
		}
	private:
		ListNode<T>* m_node;			// ListNode containing element, if nullptr this is end iterator
		List<T> const * m_list;			// List being iterated over
	};
}