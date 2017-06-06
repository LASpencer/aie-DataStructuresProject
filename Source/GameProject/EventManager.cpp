#include "stdafx.h"
#include "EventManager.h"
#include "Observer.h"

EventManager::EventManager() : m_owner(nullptr)
{
}

EventManager::EventManager(Subject * owner) : m_owner(owner)
{
}


EventManager::~EventManager()
{
}

void EventManager::addObserver(std::shared_ptr<Observer> observer)
{
	// Check if observer is already in list
	bool observerInList = false;
	las::Array<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (it->expired()) {
			// Remove expired observers
			it = m_observers.erase(it);
		}
		else {
			std::shared_ptr<Observer> current(*it);
			if (observer.get() == current.get()) {
				observerInList = true;
				break;
			}
			++it;
		}
	}
	if (!observerInList) {
		// Add new observer to list
		m_observers.push_back(observer);
	}
}

void EventManager::removeObserver(std::shared_ptr<Observer> observer)
{
	// Find observer in list
	las::Array<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (it->expired()) {
			// Remove expired observers
			it = m_observers.erase(it);
		}
		else {
			std::shared_ptr<Observer> current(*it);
			if (observer.get() == current.get()) {
				m_observers.erase(it);
				break;
			}
			++it;
		}
	}
}

void EventManager::notifyObservers(int eventID)
{
	las::Array<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (it->expired()) {
			// Remove expired observers
			it = m_observers.erase(it);
		}
		else {
			// Notify observers
			std::shared_ptr<Observer> observer(*it);
			observer->notify(m_owner, eventID);
			++it;
		}
	}
}

bool EventManager::isSubscribed(const Observer * observer) const
{
	// Find observer in list
	las::Array<std::weak_ptr<Observer>>::const_iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (!it->expired()) {
			std::shared_ptr<Observer> current(*it);
			if (observer == current.get()) {
				return true;
			}
			++it;
		}
	}
	return false;
}

void EventManager::setOwner(Subject * owner)
{
	m_owner = owner;
}
