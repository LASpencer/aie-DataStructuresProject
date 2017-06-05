#pragma once
#include "stdafx.h"
#include "Array.h"

class Observer;

class Subject
{
public:
	Subject() {};
	virtual ~Subject() {};
	//TODO subject adds and removes observers
	//TODO subject commenting
	virtual void addObserver(std::shared_ptr<Observer> observer) = 0;
	virtual void removeObserver(std::shared_ptr<Observer> observer) = 0;
	virtual void notifyObservers(int eventID) = 0;
	virtual bool isSubscribed(const Observer* observer) const = 0;

	enum event_id {
		member_set,
		member_updated,
		state_entered,
		state_exited,
		gain_focus,
		lose_focus,
		timer_start,
		timer_finished,
		mouse_over,
		click
	};
	
};

