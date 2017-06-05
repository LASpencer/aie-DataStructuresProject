#pragma once
#include "EventCondition.h"
class TimerCondition :
	public EventCondition
{
public:
	TimerCondition();
	~TimerCondition();

	virtual EventCondition* clone() const;

	virtual bool test();
	virtual void notify(Subject* subject, int eventID);

protected:
	bool m_triggered;
};

