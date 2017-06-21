#include "stdafx.h"
#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(event_id id, EntityWeakPtr other, BoxType myBox, BoxType otherBox, glm::vec2 penetration)
	: EventBase(id), m_otherEntity(other), m_myType(myBox), m_otherType(otherBox), m_penetration(penetration)
{
	if (!isValidID(id)) {
		throw std::invalid_argument("Invalid event ID");
	}
}

CollisionEvent::~CollisionEvent()
{
}

EntityWeakPtr CollisionEvent::getOtherEntity()
{
	return m_otherEntity;
}

BoxType CollisionEvent::getMyType()
{
	return m_myType;
}

BoxType CollisionEvent::getOtherType()
{
	return m_otherType;
}

glm::vec2 CollisionEvent::getPenetration()
{
	return m_penetration;
}

bool CollisionEvent::isValidID(event_id id)
{
	return id == collision;
}