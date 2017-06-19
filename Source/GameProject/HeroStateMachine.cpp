#include "stdafx.h"
#include "HeroStateMachine.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "WalkState.h"

HeroStateMachine::HeroStateMachine(Hero * hero) : m_hero(hero)
{
	//TODO add each state
	std::shared_ptr<IdleState> idle = std::make_shared<IdleState>(m_hero);
	addState(idle_state, idle);

	std::shared_ptr<CrouchState> crouch = std::make_shared<CrouchState>(m_hero);
	addState(crouch_state, crouch);

	std::shared_ptr<WalkState> walk = std::make_shared<WalkState>(m_hero);
	addState(walk_state, walk);
}

HeroStateMachine::~HeroStateMachine()
{
}
