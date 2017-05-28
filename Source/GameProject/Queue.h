#pragma once
#include "List.h"
#include <algorithm>
#include <initializer_list>
#include <stdexcept>


namespace las {
	template<typename T>
	class Queue {
	public:
		Queue() : m_list()
		{
		}

		/**Initializer list constructor
		* @param list Initializer list starting with front of queue*/
		Queue(std::initializer_list<T> list) : m_list(list) {

		}

		//TODO copy,move, assignment, destroy

		/** Gets element at front of queue
		* @return reference to front element*/
		T& front() {
			return m_list.front();
		}

		/** Gets element at front of queue
		* @return constant reference to front element*/
		const T& front()const {
			return m_list.front();
		}

		/** Gets element at back of queue
		* @return constant reference to back element*/
		const T& back()const {
			return m_list.back();
		}

		/** Gets size of queue
		* @return number of elements in queue*/
		size_t size() const {
			return m_list.size();
		}

		/** Checks if queue is empty
		* @return true if queue has no elements*/
		bool empty() const {
			return m_list.empty();
		}

		/** Enqueues element at back of queue
		* @param value element to enqueue*/
		void push(const T& value) {
			m_list.push_back(value);
		}

		/** Dequeues element at front of queue
		* @return value of element removed*/
		T pop() {
			return m_list.pop_front();
		}

	protected:
		List<T> m_list;
	};

	// Double ended queue
	template<typename T>
	class Deque : public Queue<T> {
	public:
		Deque() {

		}

		/**Initializer list constructor
		* @param list Initializer list starting with front of deque*/
		Deque(std::initializer_list<T> list) : Queue<T>(list) {

		}

		/** Gets element at back of deque
		* @return reference to back element*/
		T& back() {
			return m_list.back();
		}

		/** Enqueues element at front of deque
		* @param value of element to enqueue*/
		void push_front(const T& value) {
			m_list.push_front(value);
		}

		/** Enqueues element at back of deque
		* @param value element to enqueue*/
		void push_back(const T& value) {
			push(value);
		}

		/** Dequeues element at front of deque
		* @return value of element removed*/
		T pop_front() {
			return pop();
		}

		/** Dequeues element at back of deque
		* @return value of element removed*/
		T pop_back() {
			return m_list.pop_back();
		}

		/** Returns value of element in deque
		* @param pos position of element in deque, with back of deque as 0
		* @return constant reference to element chosen*/
		const T& peek(size_t pos) const {
			if (empty()) {
				throw std::logic_error("Empty queue has no elements");
			}
			if (pos >= size()) {
				return m_list.back();
			} else{
				List<T>::const_iterator element = m_list.begin();
				element = element + pos;
				return *element;
			}
		}
	};
}