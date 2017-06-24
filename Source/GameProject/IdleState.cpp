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
	EntityPtr hero(m_hero);
	// Idle pose
	m_controller->setPose(HeroController::idle);
	aie::Input* input = aie::Input::getInstance();
	if (!m_onFloor) {
		// Fall if floor not touched last update
		m_shouldTransition = true;
		m_target = HeroStateMachine::fall_state;
	} else if (input->isKeyDown(jump_button)) {
		// Jump
		m_shouldTransition = true;
		m_target = HeroStateMachine::jump_state;
	} else if (input->isKeyDown(left_move_button) || input->isKeyDown(right_move_button)) {
		// Walk
		m_shouldTransition = true;
		m_target = HeroStateMachine::walk_state;
	} else if (input->isKeyDown(crouch_button)){
		// Crouch
		m_shouldTransition = true;
		m_target = HeroStateMachine::crouch_state;
	}
	GroundState::update(deltaTime);
}


void IdleState::notify(Subject * subject, EventBase * event)
{
	GroundState::notify(subject, event);
}

