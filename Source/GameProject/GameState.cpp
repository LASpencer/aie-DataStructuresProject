#include "stdafx.h"
#include "GameState.h"
#include "Transition.h"
#include "EventCondition.h"
#include "ComplexCondition.h"
#include "Event.h"

GameState::GameState(GameProjectApp* app) : m_app(app), m_focus(false), m_eventManager(this)
{
}


GameState::~GameState()
{
}

GameState::GameState(const GameState & other) : StackState(other), m_app(other.m_app), m_focus(other.m_focus), m_eventManager(this)
{
	//TODO copy gamestate
	//Copy over transitions and conditions
	// Transitions
	for (std::shared_ptr<Transition> transition : other.m_transitions) {
		std::pair<bool, std::shared_ptr<Condition>> conditionCopy = copyConditionIfSubscribed(transition->getCondition(), other);
		if(conditionCopy.first){
			addTransition(std::make_shared<Transition>(conditionCopy.second, transition->getTargetID()));
		} else {
			addTransition(transition);
		}
	}
	// Push transitions
	for (std::shared_ptr<Transition> transition : other.m_pushTransitions) {
		std::pair<bool, std::shared_ptr<Condition>> conditionCopy = copyConditionIfSubscribed(transition->getCondition(), other);
		if (conditionCopy.first) {
			addPushTransition(std::make_shared<Transition>(conditionCopy.second, transition->getTargetID()));
		}
		else {
			addPushTransition(transition);
		}
	}
	// Pop conditions
	for (std::shared_ptr<Condition> condition : other.m_popConditions) {
		std::pair<bool, std::shared_ptr<Condition>> conditionCopy = copyConditionIfSubscribed(condition, other);
		if (conditionCopy.first) {
			addPopCondition(conditionCopy.second);
		}
		else {
			addPopCondition(condition);
		}
	}
}


void GameState::onEnter()
{
	m_focus = true;
	Event wasEntered(EventBase::state_entered);
	notifyObservers(&wasEntered);
}

void GameState::onExit()
{
	Event wasExited(EventBase::state_exited);
	notifyObservers(&wasExited);
}

void GameState::onFocus()
{
	m_focus = true;
	Event gainedFocus(EventBase::gain_focus);
	notifyObservers(&gainedFocus);
}

void GameState::onLoseFocus()
{
	m_focus = false;
	Event lostFocus(EventBase::lose_focus);
	notifyObservers(&lostFocus);
}

void GameState::addObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.addObserver(observer);
}

void GameState::removeObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.removeObserver(observer);
}

void GameState::notifyObservers(EventBase* event)
{
	m_eventManager.notifyObservers(event);
}

bool GameState::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}

std::pair<bool, std::shared_ptr<Condition>> GameState::copyConditionIfSubscribed(std::shared_ptr<const Condition> condition, const GameState & other)
{
	//TODO if Condition is compound, recursively call to build up each part if necessary
	const EventCondition* subscriber = dynamic_cast<const EventCondition*>(condition.get());
	const ComplexCondition* complex = dynamic_cast<const ComplexCondition*>(condition.get());
	if (subscriber != nullptr) {
		if (other.isSubscribed(subscriber)) {
			// Must copy condition
			std::shared_ptr<EventCondition> conditionCopy(subscriber->clone());
			addObserver(conditionCopy);
			return std::make_pair(true, conditionCopy);
		}
	}
	else if (complex != nullptr) {
		//TODO check if NotCondition or BinaryCondition, and call on either part
	}
	return std::make_pair(false, std::shared_ptr<EventCondition>());
}
