#pragma once
#include "stdafx.h"
#include "State.h"
#include "Map.h"
#include "Array.h"
#include "Stack.h"

//TODO comment state machine
template <typename S, typename = std::enable_if<std::is_base_of<State,S>::value>>	//S is class derived from State abstract class
class StateMachine {
public:
	StateMachine() {

	};

	//TODO deep copy based on clone
	//StateMachine(const StateMachine& other) : m_currentID(other.m_currentID) {
	//	
	//}

	bool addState(int id, std::shared_ptr<S> newState) {
		bool success = m_states.insert(id, newState);
		//If no current state, this is now current state
		if (!m_currentState) {
			forceState(id);
		}
		return success;
	}

	void forceState(int id) {
		// If going to same state, no transition
		if (!m_currentState || m_currentID != id) {
			m_currentID = id;
			std::shared_ptr<S> newState;
			//Throws exception if id doesn't exist
			try {
				newState = m_states.at(id);
			}
			catch (const std::out_of_range& e) {
				throw std::out_of_range("No state with given id exists in state machine");
			}
			if (m_currentState) {
				m_currentState->onExit();
			}
			newState->onEnter();
			m_currentState = newState;
		}
	}

	virtual void update(float deltaTime) {
		//TODO exception instead?
		assert(m_currentState);	//Assert current state not null
		m_currentState->update(deltaTime);
		if (m_currentState->shouldTransition()) {
			forceState(m_currentState->getTarget());
		}
	}

	virtual void draw(aie::Renderer2D* renderer) {
		assert(m_currentState);
		m_currentState->draw(renderer);
	}

	std::shared_ptr<S> getState() {
		return m_currentState;
	}

protected:
	int m_currentID;
	std::shared_ptr<S> m_currentState;
	las::Map<int, std::shared_ptr<S>> m_states;
};

template <typename S, typename = std::enable_if<std::is_base_of<StackState, S>::value>>	//S is class derived from StackState abstract class
class StateStackMachine{
public:
	StateStackMachine() {

	}

	//TODO deep copy

	bool addState(int id, std::shared_ptr<S> newState) {
		bool success = m_states.insert(id, newState);
		//If no current state, this is now current state
		if (m_stateStack.empty()) {
			forceState(id);
		}
		return success;
	}

	virtual void forceState(int id) {
		// If going to same state, no transition
		// Otherwise, pop until state wanted reached. If stack emptied, push state
		bool stateInStack = false;
		for (size_t i = 0; i < m_stateStack.size(); ++i) {
			if (m_stateStack.peek(i) == id) {
				stateInStack = true;
				break;
			}
		}
		//Throws exception if id doesn't exist
		std::shared_ptr<S> newState;
		try {
			newState = m_states.at(id);
		}
		catch (const std::out_of_range& e) {
			throw std::out_of_range("No state with given id exists in state machine");
		}
		while (m_stateStack.empty() || m_stateStack.top() != id) {
			if (m_stateStack.empty()) {
				newState->onEnter();
				m_stateStack.push(id);
			}
			else {
				m_states.at(m_stateStack.pop())->onExit();
			}
		}
	}

	void forcePushState(int id) {
		// If state already in stack, don't push it on again
			bool stateInStack = false;
			for (size_t i = 0; i < m_stateStack.size(); ++i) {
				if (m_stateStack.peek(i) == id) {
					stateInStack = true;
					break;
				}
			}
			if (!stateInStack) {
				std::shared_ptr<S> newState;
				//Throws exception if id doesn't exist
				try {
					newState = m_states.at(id);
				}
				catch (const std::out_of_range& e) {
					throw std::out_of_range("No state with given id exists in state machine");
				}
				if (!m_stateStack.empty()) {
					m_states.at(m_stateStack.top())->onLoseFocus();
				}
				newState->onEnter();
				m_stateStack.push(id);
			}
	}

	void forcePopState() {
		if (m_stateStack.size() > 1) {		//Cannot pop last state in stack
			m_states.at(m_stateStack.pop())->onExit();
			m_states.at(m_stateStack.top())->onFocus();
		}
	}

	virtual void update(float deltaTime) {
		//TODO exception instead?
		assert(!m_stateStack.empty());	//Assert stack not empty
		for (size_t i = 0; i < m_stateStack.size(); ++i) {
			m_states.at(m_stateStack.peek(i))->update(deltaTime);
		}
		std::shared_ptr<S> currentState = m_states.at(m_stateStack.top())
		if (currentState->shouldPop()) {
			forcePopState();
		} else if (currentState->shouldPush()){
			forcePushState(currentState->getTarget());
		} else if (currentState->shouldTransition()){
			forceState(currentState->getTarget());
		}
	}

	virtual void draw(aie::Renderer2D* renderer) {
		assert(!m_stateStack.empty());
		for (size_t i = m_stateStack.size(); i > 0; ++i) {
			m_states.at(m_stateStack.peek(i - 1))->draw(renderer);
		}
	}

	std::shared_ptr<S> getCurrentState() {
		return m_states.at(m_stateStack.top());
	}

	std::shared_ptr<S> getState(int id) {
		return m_states.at(id);
	}

	const las::Stack<int>* getStateStack() {
		return &m_stateStack;
	}

protected:
	las::Stack<int> m_stateStack;
	las::Map<int, std::shared_ptr<S>> m_states;
};