#include "stdafx.h"
#include "OnClickCondition.h"
#include "Subject.h"
#include "EventBase.h"

OnClickCondition::OnClickCondition() : m_clicked(false), m_subscribed(false)
{
}


OnClickCondition::~OnClickCondition()
{
}

OnClickCondition::OnClickCondition(const OnClickCondition & other) : EventCondition(other), m_clicked(false),m_subscribed(false)
{
}

EventCondition * OnClickCondition::clone() const
{
	return new OnClickCondition(*this);
}

bool OnClickCondition::test()
{
	return m_clicked;
}

void OnClickCondition::notify(Subject * subject, EventBase* event)
{
	switch (event->getEventID()) {
	case(EventBase::event_id::clicked):
		m_clicked = true;
		break;
	case(EventBase::event_id::frame_start):
		m_clicked = false;
	case(EventBase::event_id::destroyed):
		m_subscribed = false;
		break;
	default:
		break;
	}
}

bool OnClickCondition::addSubject(Subject* subject)
{
	if (m_subscribed) {
		return false;
	} else {
		m_subscribed = true;
		return true;
	}
}

void OnClickCondition::removeSubject(Subject * subject)
{
	m_subscribed = false;
}


