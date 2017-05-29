#pragma once
#include "stdafx.h"
#include "Array.h"


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
			return m_array.pop_back();
		}

		/** Returns value of top element of stack
		* @return top element of stack*/
		T& top() {
			if (empty()) {
				throw std::logic_error("Empty stack has no top element");
			}
			return *(m_array.end() - 1);
		}

		/** Returns value of top element of stack
		* @return top element of stack*/
		const T& top() const {
			if (empty()) {
				throw std::logic_error("Empty stack has no top element");
			}
			return *(m_array.end() - 1);
		}

		/** Returns value of element in stack
		* @param pos number of elements above element chosen
		* @return constant reference to element chosen*/
		const T& peek(size_t pos = 0) const{
			if (empty()) {
				throw std::logic_error("Empty stack has no elements");
			}
			Array<T>::const_iterator element;
			if (pos >= m_array.size()) {
				element = m_array.begin();
			}
			else {
				element = m_array.end() - (pos + 1);
			}
		return	*element;
		}

	private:
		Array<T> m_array;
	};
}