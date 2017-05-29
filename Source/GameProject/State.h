#pragma once
#include "stdafx.h"
#include "Array.h"

class Transition;
class Condition;

//TODO comment State
class State {
public:
	State();

	virtual ~State();

	// Called when transitioning to the state
	virtual void onEnter() = 0;

	// Called when transitioning from the state
	virtual void onExit() = 0;

	/** Add a transition to another state
	* @param transition object defining conditions of transition and key of next state*/
	void addTransition(std::shared_ptr<Transition> transition);

	/** Check if any transition should occur
	* @return pair containing whether a transition was found, and if so the key to that transition*/
	std::pair<bool, int> checkTransitions();

protected:
	las::Array<std::shared_ptr<Transition>> m_transitions;
};

class StackState : public State {
public:
	StackState();

	virtual ~StackState();

	// Called when state above is popped
	virtual void onFocus() = 0;

	// Called when a state is pushed onto this
	virtual void onLoseFocus() = 0;

	/** Add a transition to another state being pushed
	* @param transition object defining conditions of transition and key of state to push*/
	void addPushTransition(std::shared_ptr<Transition> transition);

	/** Add a condition under which this state is popped
	* @param condition object containing test to determine whether object is pushed*/
	void addPopCondition(std::shared_ptr<Condition> condition);

	/** Check if any states should be pushed onto this
	* @return pair containing whether a transition was found, and if so the key of the state to push*/
	std::pair<bool, int> checkPushTransitions();

	/** Check if state should be popped
	* @return true if any pop conditions are true*/
	bool checkPopConditions();

protected:
	las::Array<std::shared_ptr<Transition>> m_pushTransitions;
	las::Array<std::shared_ptr<Condition>> m_popConditions;
};