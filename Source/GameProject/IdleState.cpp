#include "stdafx.h"
#include "IdleState.h"
#include "HeroController.h"
#include "HeroStateMachine.h"
#include "Entity.h"

IdleState::IdleState(HeroController * controller) : GroundState(controller)
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
	GroundState::onEnter();
}

void IdleState::onExit()
{
	GroundState::onExit();
}

void IdleState::update(float deltaTime)
{
	/*TODO	IdleState moves to JumpState when jump button pressed
	*		Moves to CrouchState when crouch button pressed
	*		Moves to WalkState when left or right button pressed
	*		Moves to AttackState when attack button pressed
	*		Moves to HurtState when damage taken
	*/
	EntityPtr hero(m_hero);
	m_controller->setPose(HeroController::idle);
	aie::Input* input = aie::Input::getInstance();
	if (!m_onFloor) {
		m_shouldTransition = true;
		m_target = HeroStateMachine::fall_state;
	} else if (input->isKeyDown(jump_button)) {
		m_shouldTransition = true;
		m_target = HeroStateMachine::jump_state;
	} else if (input->isKeyDown(left_move_button) || input->isKeyDown(right_move_button)) {
		m_shouldTransition = true;
		m_target = HeroStateMachine::walk_state;
	} else if (input->isKeyDown(crouch_button)){
		m_shouldTransition = true;
		m_target = HeroStateMachine::crouch_state;
	}
	GroundState::update(deltaTime);
}

void IdleState::draw(aie::Renderer2D * renderer)
{
}

void IdleState::notify(Subject * subject, EventBase * event)
{
	GroundState::notify(subject, event);
}

