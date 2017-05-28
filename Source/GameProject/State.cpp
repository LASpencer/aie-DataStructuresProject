#include "stdafx.h"
#include "State.h"
#include "Condition.h"
#include "Transition.h"

State::State()
{
}

void State::addTransition(std::shared_ptr<Transition> transition)
{
	m_transitions.push_back(transition);
}

std::pair<bool, int> State::checkTransitions()
{
	bool conditionMet = false;
	int newState = 0;
	for (std::shared_ptr<Transition> transition : m_transitions) {
		if (transition->isConditionMet()) {
			conditionMet = true;
			newState = transition->getTargetID();
			break;
		}
	}
	return std::make_pair(conditionMet, newState);
}

void StackState::addPushTransition(std::shared_ptr<Transition> transition)
{
	m_pushTransitions.push_back(transition);
}

void StackState::addPopCondition(std::shared_ptr<Condition> condition)
{
	m_popConditions.push_back(condition);
}

std::pair<bool, int> StackState::checkPushTransitions()
{
	bool conditionMet = false;
	int newState = 0;
	for (std::shared_ptr<Transition> transition : m_pushTransitions) {
		if (transition->isConditionMet()) {
			conditionMet = true;
			newState = transition->getTargetID();
			break;
		}
	}
	return std::make_pair(conditionMet, newState);
}

bool StackState::checkPopConditions()
{
	for (std::shared_ptr<Condition> condition : m_popConditions) {
		if (condition->test()) {
			return true;
		}
	}
	return false;
}
