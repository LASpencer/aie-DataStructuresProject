#pragma once
#include "EventBase.h"
#include "Collider.h"

class Entity;
typedef std::weak_ptr<Entity> EntityWeakPtr;

class CollisionEvent
	: public EventBase {
public:
	//TODO pass in all necessary variables
	CollisionEvent(event_id id);
	virtual ~CollisionEvent();

	//TODO getters
protected:
	//TODO fields for: this box, other's box, other collider, penetration
	Box m_myBox;		//TODO: should be global (ie made by multiplying collider's box by entity pos)
	Box m_otherBox;
	EntityWeakPtr m_otherEntity;
	virtual bool isValidID(event_id id);
};