#pragma once
#include "stdafx.h"
#include "State.h"
#include "Map.h"
#include "Array.h"
#include "Stack.h"

// Templated State Machine class, allowing state machines which only accept specified class of states
template <typename S, typename = std::enable_if<std::is_base_of<State,S>::value>>	//S is class derived from State abstract class
class StateMachine {
public:
	StateMachine() {

	};

	/*	Registers state with state machine
	*	@param id unique value to identify registered state
	*	@param newState State to be registered
	*	@return true if successfully added, false if id already in use*/
	bool addState(int id, std::shared_ptr<S> newState) {
		bool success = m_states.insert(id, newState);
		//If no current state, this is now current state
		if (!m_currentState) {
			forceState(id);
		}
		return success;
	}

	/*  Transitions to indicated state
	*	Throws exception if id not registered in state machine
	*@param id value identifying state registered in state machine*/
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

	// Updates current state and transition if required
	virtual void update(float deltaTime) {
		if (!m_currentState) {
			throw std::logic_error("State machine must have current state to be updated");
		}
		m_currentState->update(deltaTime);
		if (m_currentState->shouldTransition()) {
			forceState(m_currentState->getTarget());
		}
	}

	// Draws current state
	virtual void draw(aie::Renderer2D* renderer) {
		if (!m_currentState) {
			throw std::logic_error("State machine must have current state to draw");
		}
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

/*	State Machine using a stack, allowing new states to be pushed onto current state
*/
template <typename S, typename = std::enable_if<std::is_base_of<StackState, S>::value>>	//S is class derived from StackState abstract class
class StateStackMachine{
public:
	StateStackMachine() {

	}

	/*	Registers state with state machine
	*	@param id unique value to identify registered state
	*	@param newState State to be registered
	*	@return true if successfully added, false if id already in use*/
	bool addState(int id, std::shared_ptr<S> newState) {
		bool success = m_states.insert(id, newState);
		//If no current state, this is now current state
		if (m_stateStack.empty()) {
			forceState(id);
		}
		return success;
	}

	/*  Transitions to indicated state
	*	Throws exception if id not registered in state machine
	*@param id value identifying state registered in state machine*/
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

	/*  Pushes indicated state onto stack
	*	Throws exception if id not registered in state machine
	*	@param id value identifying state registered in state machine*/
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

	// Pops state on top of stack
	void forcePopState() {
		if (m_stateStack.size() > 1) {		//Cannot pop last state in stack
			m_states.at(m_stateStack.pop())->onExit();
			m_states.at(m_stateStack.top())->onFocus();
		}
	}

	// Updates all states in stack from top to bottom, and transition based on top state
	virtual void update(float deltaTime) {
		if (m_stateStack.empty()) {
			throw std::logic_error("State stack must contain states to update state machine");
		}
		for (size_t i = 0; i < m_stateStack.size(); ++i) {
			m_states.at(m_stateStack.peek(i))->update(deltaTime);
		}
		std::shared_ptr<S> currentState = m_states.at(m_stateStack.top());
		if (currentState->shouldPop()) {
			forcePopState();
		} else if (currentState->shouldPush()){
			forcePushState(currentState->getTarget());
		} else if (currentState->shouldTransition()){
			forceState(currentState->getTarget());
		}
	}

	// Draws all states in stack, from bottom to top
	virtual void draw(aie::Renderer2D* renderer) {
		if (m_stateStack.empty()) {
			throw std::logic_error("State stack must contain states to draw state machine");
		}
		for (size_t i = m_stateStack.size(); i > 0; --i) {
			m_states.at(m_stateStack.peek(i - 1))->draw(renderer);
		}
	}

	std::shared_ptr<S> getCurrentState() {
		return m_states.at(m_stateStack.top());
	}

	std::shared_ptr<S> getState(int id) {
		return m_states.at(id);
	}

	// Gets stack of state IDs
	const las::Stack<int>* getStateStack() {
		return &m_stateStack;
	}

protected:
	las::Stack<int> m_stateStack;
	las::Map<int, std::shared_ptr<S>> m_states;
};