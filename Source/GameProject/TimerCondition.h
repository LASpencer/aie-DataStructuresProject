#pragma once
#include "EventCondition.h"
class TimerCondition :
	public EventCondition
{
public:
	TimerCondition();
	~TimerCondition();
	//TODO proper copy ctor
	virtual EventCondition* clone() const;

	virtual bool test();
	virtual void notify(Subject* subject, int eventID);
	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	bool m_triggered;
	//TODO flag if already following subject
};

