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

		//TODO copy ctor, copy assign operator comments
		ListNode(const ListNode<T>& other) : m_previous(nullptr), m_next(nullptr), value(other.value)
		{}

		ListNode<T>& operator=(const ListNode<T>& other) {
			value = other.value;
			// Leave own references as they were
		}

		//TODO move ctor, move assign operator
		ListNode(ListNode<T>&& other) : m_previous(other.m_previous), m_next(other.m_next)
		{
			//TODO make sure it's moved
			value = std::move(other.value);
			//TODO does 'this' work
			if (m_previous != nullptr) {
				m_previous->setNext(this);
			}
			if (m_next != nullptr) {
				m_next->setPrevious(this);
			}
			other.setPrevious(nullptr);
			other.setNext(nullptr);
		}

		ListNode& operator=(ListNode<T>&& other) {
			//Remove self from current list, putting nodes on either side together
			if (m_previous != nullptr) {
				m_previous->m_next = m_next;
			}
			if (m_next != nullptr) {
				m_next->m_previous = m_previous;
			}
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
			//TODO check this is right way to move
			value = std::move(other.value);
		}

		//TODO dtor

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
	template <typename T> class ListConstIter;
	//TODO comment list
	template <typename T>
	class List {
	public:

		friend class ListIter<T>;
		typedef ListIter<T> iterator;
		typedef ListConstIter<T> const_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		List() : m_front(nullptr), m_back(nullptr)
		{
		}

		//TODO initializer list
		List(std::initializer_list<T> iList) : m_front(nullptr), m_back(nullptr)
		{
			for (auto element : iList) {
				push_back(element);
			}
		}
		//TODO range ctor

		//TODO fill ctor

		//TODO copy ctor, copy assignment operator (when insert range done)
		List(const List<T>& other) : m_front(nullptr), m_back(nullptr)
		{
			//TODO use insert range when written
			for (const_iterator it = other.begin(); it != other.end(); ++it) {
				push_back(*it);
			}
		}

		List<T>& operator=(const List<T>& other) {
			// Copy values into current nodes
			ListNode<T>* node = m_front;
			for (const_iterator it = other.begin(); it != other.end(); ++it) {
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

		// TODO move ctor, move assignment operator
		List(List<T>&& other) :  m_front(other.m_front),m_back(other.m_back)
		{
			other.m_front = nullptr;
			other.m_back = nullptr;

		}

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



		iterator begin() {
			return iterator(m_front, this);
		}

		iterator end() {
			return iterator(nullptr, this);
		}

		const_iterator begin() const {
			//HACK
			const_iterator begin;
			begin.m_node = m_front;
			begin.m_list = this;
			return begin;
		}
		
		const_iterator end() const {
			//return const_iterator(nullptr, this);
			//HACK 
			const_iterator end;
			end.m_list = this;
			return end;
		}

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

		const T& front() const {
			//TODO use empty()
			if (m_front == nullptr) {
				throw std::out_of_range("Empty list has no front");
			}
			return m_front->value;
		}

		const T& back() const {
			//TODO use empty()
			if (m_back == nullptr) {
				throw std::out_of_range("Empty list has no back");
			}
			return m_back->value;
		}


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
	
			return iterator(node, this);
		}

		void insert(iterator position, size_t count, const T& value) {
			//TODO fill before position with count elements of value
			if (position.m_list != this) {
				throw std::invalid_argument("position is not an iterator of this list");
			}
			if (count != 0) {
				ListNode<T>* head = new ListNode<T>(value);
				ListNode<T>* tail = head;
				for (size_t i = 1; i < count; ++i) {
					ListNode<T>* nextNode = new ListNode<T>(value, tail);
					tail->setNext(nextNode);
					tail = nextNode;
				}
				ListNode<T>* node = position.m_node;
				if (node == nullptr) {
					m_back->setNext(head);
					head->setPrevious(m_back);
					m_back = tail;
				}
				else if (node == m_front) {
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

		template <typename Iter,
			typename = typename std::enable_if<std::is_same<std::iterator_traits<Iter>::value_type, T>::value, Iter >::type> //Substitution failure if Iter is not input iterator containing T
			void insert(iterator position, Iter first, Iter last) {
			//TODO insert before position from range
		}

		iterator erase(iterator position) {
			//TODO erase element
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

		iterator erase(iterator first, iterator last) {
			//TODO erase range
			if (first.m_list != this || last.m_list != this) {
				throw std::invalid_argument("first and last must both be iterators of this list");
			}
			if (first.m_node == nullptr) {
				throw std::out_of_range("first cannot be end iterator");
			}
			// Check range is valid
			for (iterator it = first; it != last; ++it) {
				if (it == end()) {
					throw std::out_of_range("last could not be reached by iterating first");
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

		void remove(const T& value) {
			//TODO remove all with value
		}

		//TODO maybe: remove_if(predicate)

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

		size_t size() {
			//TODO count through nodes? Or keep a value?
			size_t count = 0;
			for (iterator it = begin(); it != end(); ++it) {
				++count;
			}
			return count;
		}

		bool empty() {
			return m_front == nullptr;
		}

		//TODO operator==
		bool operator==(const List<T>& other) const {		//TODO make const after const iter programmed
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

	//TODO comment ListIter
	template <typename T>
	class ListIter : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		friend class List<T>;

		ListIter() : m_node(nullptr), m_list(nullptr)
		{}

		ListIter(ListNode<T>* node, List<T>* list) :
			m_node(node), m_list(list)
		{}

		ListIter(ListIter<T>&other) : m_node(other.m_node), m_list(other.m_list)
		{
		}

		~ListIter()
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

		bool operator==(const ListIter<T>&other) const {
			//HACK what if a node can belong to multiple lists?
			return m_node == other.m_node;
		}

		bool operator!=(const ListIter<T>&other) const {
			return m_node != other.m_node;
		}

		//TODO fix this conversion
		operator ListConstIter<T>() {
			return ListConstIter<T>(m_node, m_list);
		}

		ListIter<T>& operator++() {
			if (m_node != nullptr) {
				m_node = m_node->getNext();
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
				ListNode<T>* prev = m_node->getPrevious();
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
				ListNode<T>* prev = m_node->getPrevious();
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

	template <typename T>
	class ListConstIter : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		friend class List<T>;

		ListConstIter() : m_node(nullptr), m_list(nullptr)
		{}

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

		const T& operator*() const {
			return m_node->value;
		}

		//TODO check this is right const usage
		const T* operator->() const {
			return &(m_node->value);
		}

		bool operator==(const ListConstIter<T>&other) const {
			return m_node == other.m_node;
		}

		bool operator!=(const ListConstIter<T>&other) const {
			return !(*this == other);
		}

		ListConstIter<T>& operator++() {
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return *this;
		}

		ListConstIter<T> operator++(int) {
			ListConstIter<T> old(*this);
			if (m_node != nullptr) {
				m_node = m_node->getNext();
			}
			return old;
		}

		ListConstIter<T>& operator--() {
			if (m_node != nullptr) {
				ListNode<T>* prev = m_node->getPrevious();
				if (prev != nullptr) {
					m_node = prev;
				}
			}
			else {	// If nullptr, reference final element of list
				m_node = m_list->m_back;
			}
			return *this;
		}

		ListConstIter<T> operator--(int) {
			ListConstIter<T> old(*this);
			if (m_node != nullptr) {
				ListNode<T>* prev = m_node->getPrevious();
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
		List<T> const * m_list;
	};
}