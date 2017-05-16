#pragma once
#include <initializer_list>

namespace las {

	// Template class for dynamic arrays
	template <typename T>
	class Array
	{
	public:

		static const size_t DEF_CAPACITY = 8;	// Default elements to allocate
		typedef T* iterator;
		typedef const T* const_iterator;
		

		Array() : m_size(0), m_capacity(DEF_CAPACITY)
		{
			m_array = new T[DEF_CAPACITY];
		}

		/** Constructs an array of count elements initialized to value
		* @param count number of elements in array
		* @param value value of elements*/
		Array(size_t count, T value = T()) : m_size(count), m_capacity(DEF_CAPACITY)
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
		Array(std::initializer_list<T> list) : m_size(list.size()), m_capacity(DEF_CAPACITY)
		{
			// Double capacity until enough space for elements
			while (m_size > m_capacity) {
				m_capacity *= 2;
			}
			// Allocate memory on heap
			m_array = new T[m_capacity];
			// Fill array with values
			size_t i = 0;
			for (auto element : list) {
				m_array[i] = element;
				++i;
			}
		}

		//TODO construct from range (iterator to iterator)

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
			//TODO WRONG! instead throw exception if outside size
			// If no element at index, expand array
			while (pos >= m_size) {
				push_back(T());
			}
			return m_array[pos];
		}

		/** Returns a constant reference to an element
		* @param pos index of element	*/
		const T& operator[](size_t pos) const {
			if (pos >= m_size) {
				throw std::out_of_range("pos greater than Array size");
			}
			return m_array[pos];
		}

		iterator begin() {
			return m_array[0];
		}

		iterator end() {
			return m_array[m_size]
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
				T* resizedArr = new T[m_capacity];
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
				if (m_size >= m_capacity) {
					reserve(m_size + 1);
				}
				// Shift elements forward in array
				for (size_t i = m_size; i >= pos; --i) {
					m_array[i+1] = m_array[i];
				} 
				// Insert new element at pos
				m_array[pos] = value;
				++m_size;
			}
		}

		/** Insert multiple elements into array
		*/
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
				for (size_t i = m_size; i >= pos; --i) {
					m_array[i + count] = m_array[i];
				}
				// Insert new elements into array
				// HACK check if std::copy is legal and use instead
				for (size_t i = 0; i < count; ++i) {
					m_array[pos + i] = value;
				}
				m_size += count;
			}
		}

		//TODO insert from range

		/** Erase element from array
		* @param pos index of element to erase*/
		//TODO returns iterator after erased element
		void erase(size_t pos) {
			if (pos < m_size) {
				// Move elements back, overwriting pos
				for (size_t i = pos + 1; i < m_size; ++i) {
					m_array[i - 1] = m_array[i];
				}
				// remove last element
				m_array[m_size - 1] = T();
				--m_size;
			}
		}

		//TODO erase over iterator range

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
