#include "stdafx.h"
#include "EventBase.h"



EventBase::EventBase(event_id id) : m_id(id)
{
}

EventBase::~EventBase()
{
}

EventBase::event_id EventBase::getEventID()
{
	return m_id;
}
