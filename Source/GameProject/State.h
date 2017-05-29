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

	virtual void onEnter() = 0;
	virtual void onExit() = 0;

	void addTransition(std::shared_ptr<Transition> transition);
	std::pair<bool, int> checkTransitions();

protected:
	las::Array<std::shared_ptr<Transition>> m_transitions;
};

class StackState : public State {
	StackState();

	virtual ~StackState();

	virtual void onFocus() = 0;
	virtual void onLoseFocus() = 0;

	void addPushTransition(std::shared_ptr<Transition> transition);
	void addPopCondition(std::shared_ptr<Condition> condition);
	std::pair<bool, int> checkPushTransitions();
	bool checkPopConditions();

protected:
	las::Array<std::shared_ptr<Transition>> m_pushTransitions;
	las::Array<std::shared_ptr<Condition>> m_popConditions;
};