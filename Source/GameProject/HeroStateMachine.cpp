#include "stdafx.h"
#include "Entity.h"
#include "Component.h"
#include "HeroStateMachine.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"
#include "FallState.h"
#include "JumpState.h"

HeroStateMachine::HeroStateMachine(HeroController* controller) : m_controller(controller)
{
	//TODO add each state
	addState(idle_state, std::make_shared<IdleState>(controller));
	addState(crouch_state, std::make_shared<CrouchState>(controller));
	addState(walk_state, std::make_shared<WalkState>(controller));
	addState(fall_state, std::make_shared<FallState>(controller));
	addState(jump_state, std::make_shared<JumpState>(controller));
}


HeroStateMachine::~HeroStateMachine()
{
}

void HeroStateMachine::setHero(EntityPtr hero)
{
	if ((hero->getComponentMask() & (Component::sprite | Component::collider))
		== (Component::sprite | Component::collider) &&
		(hero->getTagMask() & Entity::player)) {
		m_hero = EntityWeakPtr(hero);
		for (las::Map<int, HeroStatePtr>::iterator it = m_states.begin();
			it != m_states.end(); ++it) {
			it->second->setHero(hero);
		}
	}
	else {
		throw std::invalid_argument("Hero must have Sprite and Collider components and be tagged as Player");
	}
}
