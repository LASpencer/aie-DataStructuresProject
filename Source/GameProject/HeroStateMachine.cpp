#include "stdafx.h"
#include "HeroStateMachine.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"

HeroStateMachine::HeroStateMachine(HeroController* controller) : m_controller(controller)
{
	//TODO add each state
	std::shared_ptr<IdleState> idle = std::make_shared<IdleState>(controller);
	addState(idle_state, idle);

	std::shared_ptr<CrouchState> crouch = std::make_shared<CrouchState>(controller);
	addState(crouch_state, crouch);

	std::shared_ptr<WalkState> walk = std::make_shared<WalkState>(controller);
	addState(walk_state, walk);
}


HeroStateMachine::~HeroStateMachine()
{
}

void HeroStateMachine::setHero(EntityPtr hero)
{
	m_hero = EntityWeakPtr(hero);
	for (las::Map<int, HeroStatePtr>::iterator it = m_states.begin();
		it != m_states.end(); ++it) {
		it->second->setHero(hero);
	}
}
