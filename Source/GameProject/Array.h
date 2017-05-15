#pragma once

namespace las {

	// Template class for dynamic arrays
	template <typename T>
	class Array
	{
	public:
		Array() : m_size(0), m_capacity(8)
		{
			m_array = new T[8];
		};

		//TODO copy constructor
		//TODO copy operator

		~Array()
		{
			delete m_array;
		};

		//TODO [] operator (const and not)

		// Return size of the array
		size_t size() {
			return m_size;
		}

		// Return size of allocated storage capacity
		size_t capacity() {
			return m_capacity;
		}

	private:
		T*	m_array;

		size_t m_size;
		size_t m_capacity;

	};

}

