#include "stdafx.h"
#include "IdleState.h"
#include "Hero.h"
#include "HeroStateMachine.h"

IdleState::IdleState(Hero * hero) : HeroState(hero)
{
}

IdleState::~IdleState()
{
}

State * IdleState::clone() const
{
	return new IdleState(*this);
}

void IdleState::onEnter()
{
	HeroState::onEnter();
}

void IdleState::onExit()
{
	HeroState::onExit();
}

void IdleState::update(float deltaTime)
{
	/*TODO	IdleState moves to JumpState when jump button pressed
	*		Moves to CrouchState when crouch button pressed
	*		Moves to WalkState when left or right button pressed
	*		Moves to AttackState when attack button pressed
	*		Moves to HurtState when damage taken
	*/
	m_hero->setStance(Hero::idle);
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(left_move_button) || input->isKeyDown(right_move_button)) {
		m_shouldTransition = true;
		m_target = HeroStateMachine::walk_state;
	} else if (input->isKeyDown(crouch_button)){
		m_shouldTransition = true;
		m_target = HeroStateMachine::crouch_state;
	}
}

void IdleState::draw(aie::Renderer2D * renderer)
{
}

