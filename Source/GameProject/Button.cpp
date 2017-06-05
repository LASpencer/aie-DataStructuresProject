#include "stdafx.h"
#include "Button.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::addObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.addObserver(observer);
}

void Button::removeObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.removeObserver(observer);
}

void Button::notifyObservers(int eventID)
{
	m_eventManager.notifyObservers(eventID);
}

bool Button::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}
