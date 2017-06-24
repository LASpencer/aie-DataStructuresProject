#include "stdafx.h"
#include "JumpState.h"
#include "HeroController.h"

JumpState::JumpState(HeroController * controller) : AirState(controller)
{
}

JumpState::~JumpState()
{
}

void JumpState::onEnter()
{
	AirState::onEnter();
	// Start moving upward at jump speed
	m_controller->setVerticalSpeed(HeroController::jump_speed);
}

void JumpState::onExit()
{
	AirState::onExit();
}

void JumpState::update(float deltaTime)
{
	AirState::update(deltaTime);
	// Set jumping pose
	m_controller->setPose(HeroController::jump);
	if (m_controller->getVerticalSpeed() <= 0.f) {
		// Fall if not moving upwards
		m_shouldTransition = true;
		m_target = HeroStateMachine::fall_state;
	}
}

void JumpState::draw(aie::Renderer2D * renderer)
{
}

void JumpState::notify(Subject * subject, EventBase * event)
{
	AirState::notify(subject, event);
}
