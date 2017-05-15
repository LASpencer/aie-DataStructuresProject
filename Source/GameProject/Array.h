#pragma once

namespace las {

	// Template class for dynamic arrays
	template <typename T>
	class Array
	{
	public:

		static const size_t DEF_SIZE = 8;	// Default elements to allocate

		Array() : m_size(0), m_capacity(DEF_SIZE)
		{
			m_array = new T[DEF_SIZE];
		}

		/** Constructs an array of count elements initialized to value
		* @param count number of elements in array
		* @param value value of elements*/
		Array(size_t count, const T& value = T()) : m_size(count)
		{
			m_capacity = DEF_SIZE;
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

		/** Copy constructor
		* <param name='other'>array to copy*/
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
		*/
		T& operator=(const T& other) {
			delete m_array;
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
			delete m_array;
		}

		/** Returns a reference to an element
		* @param pos index of element*/
		T& operator[](size_t pos) {
			// If no element at index, expand array
			while (pos >= m_size) {
				push_back(T());
			}
			return m_array[pos];
		}

		/** Returns a constant reference to an element
		* @param pos index of element	*/
		const T& operator[](size_t pos) const {
			return m_array[pos];
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
				delete m_array;
				m_array = resizedArr;
			}
		}

		/** Frees memory by resizing array
		* @param capacity minimim capacity required*/
		void shrink_to_fit(size_t capacity = 0) {
			//TODO shrink to fit
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
				delete m_array;
				m_array = resizedArr;
			}
		}

		void clear() {
			//TODO clear
			// remove all elements from array
		}

		void insert(size_t pos, const T& value) {
			// TODO insert
			// insert value in space before pos
		}


		void insert(size_t pos, size_t count, const T& value) {
			//TODO insert multiple
			// insert count elements of value before pos
		}

		void erase(size_t pos) {
			// TODO erase
			// Remove element at pos
		}

		/** Insert element at end of array
		* @param value element to insert*/
		void push_back(const T& value) {
			//TODO push_back
			// Allocate memory if needed
			if (m_size >= m_capacity) {
				reserve(m_size + 1);
			}
			// insert element at end
			m_array[m_size] = value;
			++m_size;
		}

		T pop_back() {
			//TODO pop_back
			//
		}

	private:
		T*	m_array;

		size_t m_size;
		size_t m_capacity;

	};

}
