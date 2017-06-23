#include "stdafx.h"
#include "CollisionEvent.h"
#include "Entity.h"
#include "HeroController.h"
#include "AirState.h"

AirState::AirState(HeroController* controller) : HeroState(controller)
{
}

AirState::~AirState()
{
}

void AirState::onEnter()
{
	HeroState::onEnter();
}

void AirState::onExit()
{
	HeroState::onExit();
}

void AirState::update(float deltaTime)
{
	EntityPtr hero(m_hero);
	float adjustedSpeed = m_controller->getVerticalSpeed() - 0.5f*HeroController::fall_rate;
	hero->getPosition()->translate({ 0,adjustedSpeed }, false);
	m_controller->setVerticalSpeed(m_controller->getVerticalSpeed() - HeroController::fall_rate);
}

void AirState::notify(Subject * subject, EventBase * event)
{
	EntityPtr entity = m_hero.lock();
	// If vertical body-body collision, clamp vertical speed
	if (event->getEventID() == EventBase::collision) {
		CollisionEvent* collision = dynamic_cast<CollisionEvent*>(event);
		assert(collision != nullptr);
		Collider* collider = dynamic_cast<Collider*>(subject);
		if (collider != nullptr) {
			EntityPtr other = collision->getOtherEntity().lock();
			if ((entity && other) &&								// Both hero and other entity exist
				(collider == entity.get()->getComponent(Component::collider).get()) &&		// Subject was hero's collider
				(collision->getMyType() == BoxType::body) &&		// Hero's hitbox was feet
				(collision->getOtherType() == BoxType::body)) { 	// Other hitbox was body
				glm::vec2 penetration = collision->getPenetration();
				if (penetration.y > 0) {	//Hero on top of something
					m_controller->setVerticalSpeed(std::min(0.f, m_controller->getVerticalSpeed()));
				} else if (penetration.y < 0) { //Hero below something
					m_controller->setVerticalSpeed(std::max(0.f, m_controller->getVerticalSpeed()));
				}
			}
		}
		else {
			throw std::invalid_argument("Only Collider subjects should produce collision events");
		}
	}
}
