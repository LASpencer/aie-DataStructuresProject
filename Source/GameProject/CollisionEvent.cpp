#include "stdafx.h"
#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(event_id id) : EventBase(id)
{
	if (!isValidID(id)) {
		throw std::invalid_argument("Invalid event ID");
	}
}

CollisionEvent::~CollisionEvent()
{
}

bool CollisionEvent::isValidID(event_id id)
{
	return id == collision;
}
