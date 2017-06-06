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
		member_updated,		//Some variable was updated
		destroyed,			//Subject was destroyed
		frame_start,		//Subject has started new update
		state_entered,		//State was entered
		state_exited,		//State was exited
		gain_focus,			//State gained focus
		lose_focus,			//State lost focus
		timer_start,		//A timer was started
		timer_finished,		//A timer has finished
		mouse_over,			//The mouse cursor is over the subject
		mouse_exit,			//The mouse cursor has left the subject
		clicked				//The subject was clicked
	};
};

