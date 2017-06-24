#include "stdafx.h"
#include "WalkState.h"
#include "HeroController.h"
#include "Entity.h"

WalkState::WalkState(HeroController* controller) : GroundState(controller)
{
}

WalkState::~WalkState()
{
}

State * WalkState::clone() const
{
	return new WalkState(*this);
}

void WalkState::onEnter()
{
	GroundState::onEnter();
	// Reset walk cycle
	m_timer = 0.0f;
	m_frame = 0;
}

void WalkState::onExit()
{
	GroundState::onExit();
}

void WalkState::update(float deltaTime)
{
	EntityPtr hero(m_hero);
	assert(hero);
	m_timer += deltaTime;
	// Advance walk cycle
	if (m_timer > HeroController::move_frame_length) {
		m_timer -= HeroController::move_frame_length;
		++m_frame;
	}
	if (m_frame > 7) {
		m_frame = 0;
	}
	// Set pose as appropriate frame of walk cycle
	m_controller->setPose(HeroController::Pose(HeroController::run1 + m_frame));
	if (!m_onFloor) {
		// Fall if floor not touched last frame
		m_shouldTransition = true;
		m_target = HeroStateMachine::fall_state;
	}
	else {
		aie::Input* input = aie::Input::getInstance();
		if (input->isKeyDown(jump_button)) {
			//Jump
			m_shouldTransition = true;
			m_target = HeroStateMachine::jump_state;
		}
		else if (input->isKeyDown(HeroState::right_move_button)) {
			// Face right
			if (hero->getPosition()->getGlobalTransform()[0][0] < 0.0f) {
				hero->getPosition()->applyTransform({ -1,0,0,0, 1,0,0,0,1 });
			}
		}
		else if (input->isKeyDown(HeroState::left_move_button)) {
			// Face left
			if (hero->getPosition()->getGlobalTransform()[0][0] > 0.0f) {
				hero->getPosition()->applyTransform({ -1,0,0,0, 1,0,0,0,1 });
			}
		}
		else {
			// Idle if no input pressed
			m_shouldTransition = true;
			m_target = HeroStateMachine::idle_state;
		}
		// Move forward
		hero->getPosition()->translate({ HeroController::move_speed * deltaTime,0 });
	}
	GroundState::update(deltaTime);
}

void WalkState::draw(aie::Renderer2D * renderer)
{
}

void WalkState::notify(Subject * subject, EventBase * event)
{
	GroundState::notify(subject, event);
}
