#include "stdafx.h"
#include "CrouchState.h"
#include "HeroStateMachine.h"
#include "HeroController.h"
#include "Entity.h"

CrouchState::CrouchState(HeroController* controller) : HeroState(controller)
{
}

CrouchState::~CrouchState()
{
}

State * CrouchState::clone() const
{
	return new CrouchState(*this);
}

void CrouchState::onEnter()
{
	HeroState::onEnter();
}

void CrouchState::onExit()
{
	HeroState::onExit();
}

void CrouchState::update(float deltaTime)
{
	/*TODO	Moves to IdleState on release crouch button
	*		Moves to CrouchAttackState on pressing attack button
	*		Moves to JumpState on pressing jump button
	*		Moves to CrouchHurtState on taking damage
	*/
	m_controller->setPose(HeroController::crouch);
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyUp(crouch_button)) {
		m_shouldTransition = true;
		m_target = HeroStateMachine::idle_state;
	}
}

void CrouchState::draw(aie::Renderer2D * renderer)
{
}

void CrouchState::notify(Subject * subject, EventBase * event)
{
}
