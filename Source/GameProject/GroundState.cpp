#include "stdafx.h"
#include "CollisionEvent.h"
#include "Entity.h"
#include "GroundState.h"

GroundState::GroundState(HeroController * controller) : HeroState(controller), m_onFloor(true)
{
}

GroundState::~GroundState()
{
}

void GroundState::onEnter()
{
	HeroState::onEnter();
	// Assume entry means hero touched floor
	m_onFloor = true;
}

void GroundState::onExit()
{
	HeroState::onExit();
}

void GroundState::update(float deltaTime)
{
	// If feet collide with floor, this will be set back to true
	m_onFloor = false;
}

void GroundState::notify(Subject * subject, EventBase * event)
{
	EntityPtr entity = m_hero.lock();
	// If feet to floor body collision, onFloor is true
	if (event->getEventID() == EventBase::collision) {
		CollisionEvent* collision = dynamic_cast<CollisionEvent*>(event);
		assert(collision != nullptr);
		Collider* collider = dynamic_cast<Collider*>(subject);
		if (collider != nullptr) {
			EntityPtr other = collision->getOtherEntity().lock();
			if ((entity && other) &&								// Both hero and other entity exist
				(other->getTagMask() & Entity::floor) &&			// Other entity is a floor
				(collider == entity.get()->getComponent(Component::collider).get()) &&		// Subject was hero's collider
				(collision->getMyType() == BoxType::feet) &&		// Hero's hitbox was feet
				(collision->getOtherType() == BoxType::body)) { 	// Other hitbox was body
				// Hero is supported by floor
				m_onFloor = true;
			}
		} else {
			throw std::invalid_argument("Only Collider subjects should produce collision events");
		}
	}
}


