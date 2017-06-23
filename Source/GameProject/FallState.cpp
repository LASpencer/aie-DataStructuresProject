#include "stdafx.h"
#include "HeroController.h"
#include "CollisionEvent.h"
#include "Entity.h"
#include "FallState.h"

FallState::FallState(HeroController * controller) : AirState(controller)
{
}

FallState::~FallState()
{
}

State * FallState::clone() const
{
	return new FallState(*this);
}

void FallState::onEnter()
{
	AirState::onEnter();
	m_controller->setVerticalSpeed(std::max(0.f, m_controller->getVerticalSpeed()));
}

void FallState::onExit()
{
	AirState::onExit();
}

void FallState::update(float deltaTime)
{
	AirState::update(deltaTime);
	EntityPtr hero(m_hero);
	m_controller->setPose(HeroController::falling);
}

void FallState::draw(aie::Renderer2D * renderer)
{
}

void FallState::notify(Subject * subject, EventBase * event)
{
	AirState::notify(subject, event);
	// If collided with floor from above, transition to idle state
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
				(other->getTagMask() & Entity::floor) &&			// Other entity is floor 
				(collision->getMyType() == BoxType::body) &&		// Hero's hitbox was body
				(collision->getOtherType() == BoxType::body)) { 	// Other hitbox was body
				glm::vec2 penetration = collision->getPenetration();
				if (penetration.y > 0) {	//Hero on top of something
					m_shouldTransition = true;
					m_target = HeroStateMachine::idle_state;
				}
			}
		}
		else {
			throw std::invalid_argument("Only Collider subjects should produce collision events");
		}
	}
}
