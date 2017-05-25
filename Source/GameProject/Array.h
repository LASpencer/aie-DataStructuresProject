#pragma once
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <functional>

namespace las {

	// Template class for dynamic arrays
	template <typename T>
	class Array
	{
	public:

		static const size_t def_capacity = 8;	// Default elements to allocate
		typedef T* iterator;
		typedef const T* const_iterator;
		

		Array() : m_size(0), m_capacity(def_capacity)
		{
			m_array = new T[def_capacity];
		}

		/** Constructs an array of count elements initialized to value
		* @param count number of elements in array
		* @param value value of elements*/
		Array(size_t count, T value = T()) : m_size(count), m_capacity(def_capacity)
		{
			// Double capacity until enough space for elements
			while (count > m_capacity) {
				m_capacity *= 2;
			} 
			// Allocate memory on heap
			m_array = new T[m_capacity];
			// Fill array with values
			for (size_t i = 0; i < count; ++i) {
				m_array[i] = value;
			}
		}

		/** Constructs an array from initializer list
		* @param list initializer list of elements*/
		Array(std::initializer_list<T> list) : m_size(list.size()), m_capacity(def_capacity)
		{
			// Double capacity until enough space for elements
			while (m_size > m_capacity) {
				m_capacity *= 2;
			}
			// Allocate memory on heap
			m_array = new T[m_capacity];
			// Fill array with values
			size_t i = 0;
			for (T element : list) {
				m_array[i] = element;
				++i;
			}
		}

		/** Range constructor 
		* @param first input iterator to first element in range
		* @param last input iterator to end of range*/
		//TODO documentation
		template <typename Iter,
		typename = typename std::enable_if<std::is_same<std::iterator_traits<Iter>::value_type, T>::value, Iter >::type> //Substitution failure if Iter is not input iterator containing T
		Array(Iter first, Iter last) : m_capacity(def_capacity)	//TODO document distance may cause undefined
		{
			if (std::is_base_of<std::forward_iterator_tag, std::iterator_traits<Iter>::iterator_category>::value){	//Check multipass guarantee
				int distance = std::distance(first, last);
				if (distance < 0) {
					throw std::invalid_argument("last must be reachable by incrementing first");
				}
				m_size = distance;
																// Double capacity until enough space for elements
				while (m_size > m_capacity) {
					m_capacity *= 2;
				}
				//Allocate memory on heap
				m_array = new T[m_capacity];
				// Fill array with values
				size_t i = 0;
				for (Iter it = first; it != last; ++it)
				{
					m_array[i] = *it;
					++i;
				}
			}
			else {	// Multipass guarantee does not hold, so distance cannot be checked
				m_size = 0;
				m_array = new T[m_capacity];
				for (Iter it = first; it != last; ++it) {
					push_back(*it);
				}
			}
		}


		/** Copy constructor
		* @param other array to copy*/
		Array(const Array<T>& other) : m_size(other.m_size), m_capacity(other.m_capacity)
		{
			// Allocate memory on heap
			m_array = new T[m_capacity];
			// Copy values from other array
			for (size_t i = 0; i < m_size; ++i) {
				m_array[i] = other.m_array[i];
			}
		}

		/** copy assignment operator
		* @param other array to copy*/
		Array<T>& operator=(const Array<T>& other) {
			delete[] m_array;
			m_size = other.m_size;
			m_capacity = other.m_capacity;
			m_array = new T[m_capacity];
			for (size_t i = 0; i < m_size; ++i) {
				m_array[i] = other.m_array[i];
			}
			return *this;
		}

		~Array()
		{
			delete[] m_array;
		}

		/** Returns a reference to an element
		* @param pos index of element*/
		T& operator[](size_t pos) {
			if (pos >= m_size) {
				throw std::out_of_range("pos is past last element");
			}
			return m_array[pos];
		}

		/** Returns a constant reference to an element
		* @param pos index of element	*/
		const T& operator[](size_t pos) const {
			if (pos >= m_size) {
				throw std::out_of_range("pos is past last element");
			}
			return m_array[pos];
		}

		iterator begin() const {
			return &(m_array[0]);
		}

		iterator end() const {
			return &(m_array[m_size]);
		}

		/** Equality operator
		* @param other array of same type to be compared
		* @return true if sizes equal and all elements equal*/
		const bool operator==(const Array<T>& other) {
			bool equal;
			// Check equal sizes
			if (m_size == other.m_size) {
				// If equal size, check for matching values
				equal = true;
				for (size_t i = 0; i < m_size; ++i) {
					if (m_array[i] != other.m_array[i]) {
						equal = false;
						break;
					}
				}
			} else{
				equal = false;
			}
			return equal;
		}

		const bool operator!=(const Array<T>& other) {
			return !(*this==(other));
		}

		/** Return size of the array
		* @return number of elements in array*/
		size_t size() const {
			return m_size;
		}

		/* Return size of allocated storage capacity
		* @return number of elements memory was allocated for*/
		size_t capacity() const {
			return m_capacity;
		}

		/** Checks if the container has no elements
		* @return boolean indicating whether array has any elements*/
		bool empty() const {
			return m_size == 0;
		}

		/** Allocates additional memory
		* @param capacity minimum capacity required*/
		void reserve(size_t capacity) {
			//if capacity > m_capacity, allocate more memory 
			if (capacity > m_capacity) {
				// Increase capacity until larger than requested
				while (m_capacity < capacity) {
					m_capacity *= 2;
				}
				// Create new array
				T* resizedArr = new T[m_capacity];	//HACK deal with bad_alloc
				// Copy elements to new array
				for (size_t i = 0; i < m_size; ++i) {
					resizedArr[i] = m_array[i];
				}
				delete[] m_array;
				m_array = resizedArr;
			}
		}

		/** Frees memory by resizing array
		* @param capacity minimim capacity required*/
		void shrink_to_fit(size_t capacity = 0) {
			// Resize to size or capacity, whichever is greater
			size_t capNeeded = std::max(capacity, m_size);
			size_t newCapacity = 2;
			while (newCapacity < capNeeded) {
				newCapacity *= 2;
			}
			if (newCapacity < m_capacity) {
				m_capacity = newCapacity;
				T* resizedArr = new T[m_capacity];
				for (size_t i = 0; i < m_size; ++i) {
					resizedArr[i] = m_array[i];
				}
				delete[] m_array;
				m_array = resizedArr;
			}
		}

		/** Erases all elements in array
		*/
		void clear() {
			// destroy all elements
			delete[] m_array;
			// allocate new array with no elements
			m_array = new T[m_capacity];
			m_size = 0;
		}

		/** Insert element into array
		* @param pos position to insert element at
		* @param value value of new element*/
		void insert(size_t pos, const T& value) {
			// If inserting at or past end, push back to end
			if (pos >= m_size) {
				push_back(value);
			}
			else {// insert value in space before pos
				// Reallocate memory if needed
				if (m_size +1 > m_capacity) {
					reserve(m_size + 1);
				}
				// Shift elements forward in array
				for (size_t i = m_size; i > pos; --i) {
					m_array[i] = m_array[i-1];
				} 
				// Insert new element at pos
				m_array[pos] = value;
				++m_size;
			}
		}

		/** Insert multiple elements into array
		* @param pos position to insert element at
		* @param value value of new element
		* @param count number of elements to insert */
		void insert(size_t pos, const T& value, size_t count) {
			// If inserting at or past end, push back to end
			if (pos >= m_size) {
				push_back(value, count);
			}else {// Insert elements in space before pos
				//Reallocate memory if needed
				if (m_size + count > m_capacity) {
					reserve(m_size + count);
				}
				// Shift elements forward in array
				for (size_t i = m_size+count; i > pos; --i) {
					m_array[i] = m_array[i-count];
				}
				// Insert new elements into array
				// HACK check if std::copy is legal and use instead
				for (size_t i = 0; i < count; ++i) {
					m_array[pos + i] = value;
				}
				m_size += count;
			}
		}

		/** Insert element into array
		* @param pos iterator of element to insert before
		* @param value value of new element*/
		void insert(iterator pos, const T& value) {
			if (std::less<iterator>()(pos, begin()) || std::greater<iterator>()(pos, end())) {
				throw std::out_of_range("pos must be within Array.begin() and Array.end()");
			}
			size_t index = pos - begin();
			insert(index, value);
		}

		/** Insert multiple elements into array
		* @param pos iterator of element to insert before
		* @param value value of new element
		* @param count number of elements to insert */
		void insert(iterator pos, const T& value, size_t count) {
			if (std::less<iterator>()(pos, begin()) || std::greater<iterator>()(pos, end())) {
				throw std::out_of_range("pos must be within Array.begin() and Array.end()");
			}
			size_t index = pos - begin();
			insert(index, value, count);
		}

		/** Insert from range
		* @param pos iterator of element to insert before
		* @param first start of range to insert from
		* @param last end of range to insert from*/
		template <typename Iter,
			typename = typename std::enable_if<std::is_same<std::iterator_traits<Iter>::value_type, T>::value, Iter >::type> //Substitution failure if Iter is not input iterator containing T
			void insert(iterator pos, Iter first, Iter last) {
			// Check pos is within range
			if (std::less<iterator>()(pos, begin()) || std::greater<iterator>()(pos, end())) {
				throw std::out_of_range("pos must be within Array.begin() and Array.end()");
			}
			/*TODO check if inserting from self, and if so throw an exception for using invalid iterators
			*/
			//if pos == end() or greater, push back each in range
			if (pos==end()) {
				for (Iter it = first; it != last; ++it) {
					push_back(*it);
				}
			}
			else {
				// Get index of element pointed to by pos
				size_t index = pos - begin();
				if (std::is_base_of<std::forward_iterator_tag, std::iterator_traits<Iter>::iterator_category>::value) {
					int distance = std::distance(first, last);
					if (distance < 0) {
						throw std::invalid_argument("last must be reachable by incrementing first");
					}
					// Reallocate memory if needed
					if (m_size + distance > m_capacity) {
						reserve(m_size + distance);
					}
					//Shift elements forward in array
					for (size_t i = m_size; i >= index; --i) {
						m_array[i + distance] = m_array[i];
					}
					//Insert elements from range
					for (Iter it = first; it != last; ++it) {
						m_array[index] = *it;
						++index;
					}
					m_size += distance;
				}
				else {
					// If no multipass guarantee, insert each value from range
					for (Iter it = first; it != last; ++it) {
						insert(index, *it);
						++index;
					}
				}
			}
		}

		/** Erase element from array
		* @param pos index of element to erase
		* @return iterator following erased element*/
		iterator erase(size_t pos) {
			iterator next;
			if (pos >= m_size) {
				throw std::out_of_range("Cannot erase: pos is past last element");
			}
			// Move elements back, overwriting pos
			for (size_t i = pos + 1; i < m_size; ++i) {
				m_array[i - 1] = m_array[i];
			}
			// remove last element
			--m_size;
			next = m_array + pos;
			return next;
		}

		/** Erase element from array
		* @param pos iterator of element to erase
		* @return iterator following erased element*/
		iterator erase(iterator pos) {
			if (std::less<iterator>()(pos, begin()) || std::greater_equal<iterator>()(pos, end())) {
				throw std::out_of_range("pos must be equal to or after Array.begin() and before Array.end()");
			}
			// Move elements back, overwriting pos
			for (iterator it = pos + 1; it != end(); ++it) {
				*(it - 1) = *it;
			}
			// remove last element
			--m_size;
			return pos;
		}

		/** Erase range of elements
		* @param first start of range to erase
		* @param last end of range to erase
		* @return iterator following erased element*/
		iterator erase(iterator first, iterator last) {
			if (std::less<iterator>()(first, begin()) || std::greater_equal<iterator>()(first, end())) {
				throw std::out_of_range("first must be equal to or after Array.begin() and before Array.end()");
			}
			if (std::less_equal<iterator>()(last, first) || std::greater<iterator>()(last, end())) {
				throw std::out_of_range("last must be after first and before or equal to Array.end()");
			}
			size_t distance = std::distance(first, last);
			// Move elements back, overwriting from first to last
			for (iterator it = last; it != end(); ++it) {
				*(it - distance) = *it;
			}
			// Remove elements at end
			m_size -= distance;
			return first;
		}

		/** Insert element at end of array
		* @param value element to insert*/
		void push_back(const T& value) {
			// Allocate memory if needed
			if (m_size >= m_capacity) {
				reserve(m_size + 1);
			}
			// insert element at end
			m_array[m_size] = value;
			++m_size;
		}

		/** Insert multiple elements at end of array
		* @param value element to insert
		* @param count number of elements to insert*/
		void push_back(const T& value, size_t count) {
			// Allocate memory if needed
			if (m_size + count > m_capacity) {
				reserve(m_size + count);
			}
			//HACK check if std::copy is legal and use instead if so
			for (size_t i = 0; i < count; ++i) {
				m_array[m_size] = value;
				++m_size;
			}
		}

		/** Remove last element from array
		* @return element removed*/
		T pop_back() {
			if (m_size == 0) {
				throw std::out_of_range("Cannot pop element from empty array");
			}
				T popped = m_array[m_size - 1];
				m_array[m_size - 1] = T();
				--m_size;
				return popped;
		}

	private:
		T*	m_array;

		size_t m_size;
		size_t m_capacity;

	};

}
