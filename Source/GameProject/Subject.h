#pragma once
#include "stdafx.h"
#include "Array.h"

class Observer;
class EventBase;

class Subject
{
public:
	Subject() {};
	virtual ~Subject() {};
	//TODO subject adds and removes observers
	//TODO subject commenting
	virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
	virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
	virtual void notifyObservers(EventBase* event) = 0;
	virtual bool isSubscribed(const Observer* observer) const = 0;
};

