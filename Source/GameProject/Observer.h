#pragma once

class Subject;

class Observer
{
public:
	Observer();
	virtual ~Observer();
	//TODO observer is notified by subject (virtual)

	virtual void notify(Subject* subject, int eventID) = 0;
};

