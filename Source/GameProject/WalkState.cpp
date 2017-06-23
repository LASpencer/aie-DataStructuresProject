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
	if (m_timer > HeroController::move_frame_length) {
		m_timer -= HeroController::move_frame_length;
		++m_frame;
	}
	if (m_frame > 7) {
		m_frame = 0;
	}
	m_controller->setPose(HeroController::Pose(HeroController::run1 + m_frame));
	//TODO make hero walk
	//TODO hero turns around based on direction
	/*TODO
	*		Move to JumpState on jump button pressed
	*		Move to AttackState on attack button pressed
	*		Move to HurtState on taking damage
	*		Maybe move to CrouchState on crouch press (possibly with slide?)
	*		Move to IdleState on release left/right buttons
	*/
	if (!m_onFloor) {
		m_shouldTransition = true;
		m_target = HeroStateMachine::fall_state;
	}
	else {
		aie::Input* input = aie::Input::getInstance();
		if (input->isKeyDown(jump_button)) {
			m_shouldTransition = true;
			m_target = HeroStateMachine::jump_state;
		} else if (input->isKeyDown(HeroState::right_move_button)) {
			//TODO hero turns around based on direction
			if (hero->getPosition()->getGlobalTransform()[0][0] < 0.0f) {
				hero->getPosition()->applyTransform({ -1,0,0,0, 1,0,0,0,1 });
			}
		}
		else if (input->isKeyDown(HeroState::left_move_button)) {
			//TODO hero turns around based on direction
			if (hero->getPosition()->getGlobalTransform()[0][0] > 0.0f) {
				hero->getPosition()->applyTransform({ -1,0,0,0, 1,0,0,0,1 });
			}
		} else {
			m_shouldTransition = true;
			m_target = HeroStateMachine::idle_state;
		}
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
