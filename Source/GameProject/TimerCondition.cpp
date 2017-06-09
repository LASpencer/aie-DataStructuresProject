#include "stdafx.h"
#include "TimerCondition.h"
#include "Subject.h"
#include "EventBase.h"

TimerCondition::TimerCondition() : m_triggered(false)
{
}


TimerCondition::~TimerCondition()
{
}

EventCondition * TimerCondition::clone() const
{
	return new TimerCondition(*this);
}

bool TimerCondition::test()
{
	return m_triggered;
}

void TimerCondition::notify(Subject * subject, EventBase* event)
{
	switch (event->getEventID()) {
	case(EventBase::event_id::timer_start):
		m_triggered = false;
		break;
	case(EventBase::event_id::timer_finished):
		m_triggered = true;
		break;
	default:
		break;
	}
}

bool TimerCondition::addSubject(Subject * subject)
{
	//TODO refuse if already have subject
	return true;
}

void TimerCondition::removeSubject(Subject * subject)
{
}
