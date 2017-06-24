#include "stdafx.h"
#include "CrouchState.h"
#include "HeroStateMachine.h"
#include "HeroController.h"
#include "Entity.h"

CrouchState::CrouchState(HeroController* controller) : GroundState(controller)
{
}

CrouchState::~CrouchState()
{
}

void CrouchState::onEnter()
{
	GroundState::onEnter();
}

void CrouchState::onExit()
{
	GroundState::onExit();
}

void CrouchState::update(float deltaTime)
{
	// Set crouching pose
	m_controller->setPose(HeroController::crouch);
	aie::Input* input = aie::Input::getInstance();
	if (!m_onFloor) {
		// Fall if floor not touched last update
		m_shouldTransition = true;
		m_target = HeroStateMachine::fall_state;
	} else if (input->isKeyDown(jump_button)) {
		// Jump 
		m_shouldTransition = true;
		m_target = HeroStateMachine::jump_state;
	} else if (input->isKeyUp(crouch_button)) {
		// Stand up on releasing crouch
		m_shouldTransition = true;
		m_target = HeroStateMachine::idle_state;
	}
	// Check for falling
	GroundState::update(deltaTime);
}

void CrouchState::notify(Subject * subject, EventBase * event)
{
	GroundState::notify(subject, event);
}

