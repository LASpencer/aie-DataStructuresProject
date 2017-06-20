#include "stdafx.h"
#include "GameState.h"
#include "Event.h"

GameState::GameState(GameProjectApp* app) : m_app(app), m_eventManager(this)
{
}


GameState::~GameState()
{
}

GameState::GameState(const GameState & other) : StackState(), m_app(other.m_app), m_eventManager(this)
{
	m_focus = other.m_focus;
}

GameState & GameState::operator=(const GameState & other)
{
	// Tell observers this is being destroyed and empty event manager
	Event wasDestoyed(EventBase::destroyed);
	notifyObservers(&wasDestoyed);
	m_eventManager = EventManager(this);
	m_app = other.m_app;
	m_focus = other.m_focus;
	return *this;
}


void GameState::onEnter()
{
	StackState::onEnter();
	Event wasEntered(EventBase::state_entered);
	notifyObservers(&wasEntered);
}

void GameState::onExit()
{
	StackState::onExit();
	Event wasExited(EventBase::state_exited);
	notifyObservers(&wasExited);
}

void GameState::onFocus()
{
	StackState::onFocus();
	Event gainedFocus(EventBase::gain_focus);
	notifyObservers(&gainedFocus);
}

void GameState::onLoseFocus()
{
	StackState::onLoseFocus();
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

void GameState::clearObservers()
{
	m_eventManager.clearObservers();
}

void GameState::notifyObservers(EventBase* event)
{
	m_eventManager.notifyObservers(event);
}

bool GameState::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}

