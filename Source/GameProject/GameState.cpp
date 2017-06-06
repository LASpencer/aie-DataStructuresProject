#include "stdafx.h"
#include "GameState.h"
#include "Transition.h"
#include "EventCondition.h"

GameState::GameState(GameProjectApp* app) : m_app(app), m_focus(false), m_eventManager(this)
{
}


GameState::~GameState()
{
	notifyObservers(destroyed);
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
	notifyObservers(state_entered);
}

void GameState::onExit()
{
	notifyObservers(state_exited);
}

void GameState::onFocus()
{
	m_focus = true;
	notifyObservers(gain_focus);
}

void GameState::onLoseFocus()
{
	m_focus = false;
	notifyObservers(lose_focus);
}

void GameState::addObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.addObserver(observer);
}

void GameState::removeObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.removeObserver(observer);
}

void GameState::notifyObservers(int eventID)
{
	m_eventManager.notifyObservers(eventID);
}

bool GameState::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}

std::pair<bool, std::shared_ptr<Condition>> GameState::copyConditionIfSubscribed(std::shared_ptr<const Condition> condition, const GameState & other)
{
	//TODO if Condition is compound, recursively call to build up each part if necessary
	const EventCondition* subscriber = dynamic_cast<const EventCondition*>(condition.get());
	if (subscriber != nullptr) {
		if (other.isSubscribed(subscriber)) {
			// Must copy condition
			std::shared_ptr<EventCondition> conditionCopy(subscriber->clone());
			addObserver(conditionCopy);
			return std::make_pair(true, conditionCopy);
		}
	}
	return std::make_pair(false, std::shared_ptr<EventCondition>());
}
