#include "stdafx.h"
#include "Events.h"

Event::Event()
{
}

Event::Event(event_id id) : m_id(id)
{
}

Event::event_id Event::getEventID()
{
	return m_id;
}
