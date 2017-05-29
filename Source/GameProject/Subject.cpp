#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"


Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::addObserver(std::shared_ptr<Observer> observer)
{
	// Check if observer is already in list
	bool observerInList = false;
	las::Array<std::weak_ptr<Observer>>::iterator it = m_observers.begin();
	while (it != m_observers.end()) {
		if (it->expired()) {
			// Remove expired observers
			it = m_observers.erase(it);
		} else {
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

void Subject::removeObserver(std::shared_ptr<Observer> observer)
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

void Subject::notifyObservers(int eventID)
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
			observer->notify(this, eventID);
			++it;
		}
	}
}
