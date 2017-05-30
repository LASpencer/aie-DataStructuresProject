#pragma once
#include "stdafx.h"
#include "State.h"
#include "Condition.h"
#include "Transition.h"
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

	void addTransition(std::shared_ptr<Transition> transition) {
		m_fromAnyTransitions.push_back(transition);
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

	void updateState() {
		//TODO exception instead?
		assert(m_currentState);	//Assert current state not null
		//Check transitions from any state
		for (std::shared_ptr<Transition> transition : m_fromAnyTransitions) {
			if (transition->isConditionMet()) {
				int id = transition->getTargetID();
				if (!m_currentState || m_currentID != id) {
					forceState(id);
					break;
				}
			}
		}
		// Check transitions from current state
		if (m_currentState) {
			std::pair<bool, int> maybeNewState = m_currentState->checkTransitions();
			if (maybeNewState.first) {
				forceState(maybeNewState.second);
			}
		}
	}

	std::shared_ptr<S> getState() {
		return m_currentState;
	}

protected:
	int m_currentID;
	std::shared_ptr<S> m_currentState;
	las::Map<int, std::shared_ptr<S>> m_states;
	las::Array<std::shared_ptr<Transition>> m_fromAnyTransitions;
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

	void addTransition(std::shared_ptr<Transition> transition) {
		m_fromAnyTransitions.push_back(transition);
	}

	void addPushTransition(std::shared_ptr<Transition> transition) {
		m_fromAnyPushTransitions.push_back(transition);
	}

	void addPopCondition(std::shared_ptr<Condition> condition) {
		m_popAnyConditions.push_back(condition);
	}

	virtual void forceState(int id) {
		// If going to same state, no transition
		//TODO also check if state exists somewhere in stack and instead pop down to it???
		bool stateInStack = false;
		for (size_t i = 0; i < m_stateStack.size(); ++i) {
			if (m_stateStack.peek(i).first == id) {
				stateInStack = true;
				break;
			}
		}
		if (m_stateStack.empty()||m_stateStack.top().first != id) {
			//Throws exception if id doesn't exist
			std::shared_ptr<S> newState;
			try {
				newState = m_states.at(id);
			}
			catch (const std::out_of_range& e) {
				throw std::out_of_range("No state with given id exists in state machine");
			}
			if (!m_stateStack.empty()) {
				m_stateStack.pop().second->onExit();
			}
			newState->onEnter();
			m_stateStack.push(std::make_pair(id,newState));
		}
	}

	void forcePushState(int id) {
		// If state already in stack, don't push it on again
			bool stateInStack = false;
			for (size_t i = 0; i < m_stateStack.size(); ++i) {
				if (m_stateStack.peek(i).first == id) {
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
					m_stateStack.top().second->onLoseFocus();
				}
				newState->onEnter();
				m_stateStack.push(std::make_pair(id, newState));
			}
	}

	void forcePopState() {
		if (m_stateStack.size() > 1) {		//Cannot pop last state in stack
			m_stateStack.pop().second->onExit();
			m_stateStack.top().second->onFocus();
		}
	}

	virtual void updateState() {
		//TODO exception instead?
		assert(!m_stateStack.empty());	//Assert stack not empty
		//Check pop from any state
		for (std::shared_ptr<Condition> condition : m_popAnyConditions) {
			if (condition->test()) {
				forcePopState();
				break;
			}
		}
		//Check pop from current state
		if (m_stateStack.top().second->checkPopConditions()) {
			forcePopState();
		}
		//Check transitions from any state
		for (std::shared_ptr<Transition> transition : m_fromAnyTransitions) {
			if (transition->isConditionMet()) {
				int id = transition->getTargetID();
				if (m_stateStack.top().first != id) {
					forceState(id);
					break;
				}
			}
		}
		// Check transitions from current state
		std::pair<bool, int> maybeNewState = m_stateStack.top().second->checkTransitions();
		if (maybeNewState.first) {
			forceState(maybeNewState.second);
		}
		// Check push onto any state
		for (std::shared_ptr<Transition> pushTransition : m_fromAnyPushTransitions) {
			if (pushTransition->isConditionMet()) {
				int id = pushTransition->getTargetID();
				if (m_stateStack.top().first != id) {
					forcePushState(pushTransition->getTargetID());
					break;
				}
			}
		}
		// Check push onto current state
		std::pair<bool, int> maybePushState = m_stateStack.top().second->checkPushTransitions();
		if (maybePushState.first) {
			forceState(maybePushState.second);
		}
	}

	std::shared_ptr<S> getState() {
		return m_stateStack.top().second;
	}

	las::Stack<std::shared_ptr<S>> getStateStack(bool reversed = false) {
		las::Stack<std::shared_ptr<S>> stateStack;
		size_t stackSize = m_stateStack.size();
		if (reversed) {
			for (size_t i = 0; i < stackSize; ++i) {
				stateStack.push(m_stateStack.peek(i).second);
			}
		}
		else {
			for (size_t i = 0; i < stackSize; ++i) {
				size_t pos = stackSize - (i + 1);
				stateStack.push(m_stateStack.peek(pos).second);
			}
		}
		return stateStack;
	}

protected:
	las::Stack<std::pair<int,std::shared_ptr<S>>> m_stateStack;
	las::Map<int, std::shared_ptr<S>> m_states;
	las::Array<std::shared_ptr<Transition>> m_fromAnyTransitions;
	las::Array<std::shared_ptr<Transition>> m_fromAnyPushTransitions;
	las::Array<std::shared_ptr<Condition>> m_popAnyConditions;
};