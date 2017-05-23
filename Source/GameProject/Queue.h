#pragma once
#include "List.h"
#include <algorithm>
#include <initializer_list>


namespace las {
	// TODO comment queue
	template<typename T>
	class Queue {
	public:
		Queue() : m_list()
		{
		}

		Queue(std::initializer_list<T> list) : m_list(list) {

		}

		//TODO copy,move, assignment, destroy

		T& front() {
			return m_list.front();
		}

		const T& front()const {
			return m_list.front();
		}

		const T& back()const {
			return m_list.back();
		}

		size_t size() const {
			return m_list.size();
		}

		bool empty() const {
			return m_list.empty();
		}

		void push(const T& value) {
			m_list.push_back(value);
		}

		T pop() {
			return m_list.pop_front();
		}

	protected:
		List<T> m_list;
	};

	template<typename T>
	class Deque : public Queue<T> {
	public:
		Deque() {

		}
		Deque(std::initializer_list<T> list) : Queue<T>(list) {

		}

		T& back() {
			return m_list.back();
		}

		void push_front(const T& value) {
			m_list.push_front(value);
		}

		void push_back(const T& value) {
			push(value);
		}

		T pop_front() {
			return pop();
		}

		T pop_back() {
			return m_list.pop_back();
		}

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