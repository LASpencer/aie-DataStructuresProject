#pragma once
#include "EventBase.h"
#include "Collider.h"

class Entity;
typedef std::weak_ptr<Entity> EntityWeakPtr;


class CollisionEvent
	: public EventBase {
public:
	//TODO pass in all necessary variables
	CollisionEvent(event_id id, EntityWeakPtr other, BoxType myType, BoxType otherType, glm::vec2 penetration);
	virtual ~CollisionEvent();

	EntityWeakPtr getOtherEntity();

	BoxType getMyType();

	BoxType getOtherType();

	glm::vec2 getPenetration();

protected:
	//TODO fields for: this box, other's box, other collider, penetration
	EntityWeakPtr m_otherEntity;
	BoxType m_myType;		
	BoxType m_otherType;
	glm::vec2 m_penetration;
	virtual bool isValidID(event_id id);
};