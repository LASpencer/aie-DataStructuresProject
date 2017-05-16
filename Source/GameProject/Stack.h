#pragma once
#include "Array.h"
#include <algorithm>
#include <initializer_list>

//TODO commenting

namespace las {

	template<typename T>
	class Stack {
	public:
		Stack() : m_array()
		{
		}

		Stack(std::initializer_list<T> list) : m_array(list)
		{
		}

		/** Checks if the stack has no elements
		* @return boolean indicating if the stack has no elements*/
		bool empty() const {
			return m_array.empty();
		}

		/* Returns number of elements in stack
		* @return elements in stack*/
		size_t size() const {
			return m_array.size();
		}

		/** Adds an element to the top of the stack
		* @param value element to be added*/
		void push(const T& value) {
			m_array.push_back(value);
		}

		/** Removes element from top of stack
		* @return element removed from stack*/
		T pop() {
			//TODO document exception if empty stack
			return m_array.pop_back();
		}

		/** Returns value of top element of stack
		* @return top element of stack*/
		T top() const {
			//TODO document exception if empty stack
			T top = m_array[m_array.size() - 1];
			return top;
		}

		/** Returns value of element in stack
		* @param pos number of elements above element chosen
		* @return constant reference to element chosen*/
		const T& peek(size_t pos) const {
			//TODO document exception if empty stack
			size_t index;
			if (pos >= m_array.size()) {
				index = 0;
			}
			else {
				index = m_array.size() - (pos + 1);
			}
		return	m_array[index];
		}

	private:
		Array<T> m_array;
	};
}