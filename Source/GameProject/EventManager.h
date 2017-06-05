#pragma once
#include "Subject.h"
class EventManager :
	public Subject
{
public:
	EventManager();
	EventManager(Subject* owner);
	~EventManager();

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);

	virtual void notifyObservers(int eventID);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	las::Array<std::weak_ptr<Observer>> m_observers;
	Subject* m_owner;
};
