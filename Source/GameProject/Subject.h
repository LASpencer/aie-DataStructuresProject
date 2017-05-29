#pragma once
#include "stdafx.h"
#include "Array.h"

class Observer;

class Subject
{
public:
	Subject();
	virtual ~Subject();
	//TODO subject adds and removes observers
	//TODO subject commenting
	void addObserver(std::shared_ptr<Observer> observer);
	void removeObserver(std::shared_ptr<Observer> observer);
	void notifyObservers(int eventID);
	enum event_id {
		member_set,
		member_updated
	};

protected:
	las::Array<std::weak_ptr<Observer>> m_observers;
};

