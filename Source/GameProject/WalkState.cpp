#include "stdafx.h"
#include "WalkState.h"
#include "Hero.h"

WalkState::WalkState(Hero * hero) : HeroState(hero)
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
	HeroState::onEnter();
	m_timer = 0.0f;
	m_frame = 0;
}

void WalkState::onExit()
{
	HeroState::onExit();
}

void WalkState::update(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer > Hero::move_frame_length) {
		m_timer -= Hero::move_frame_length;
		++m_frame;
	}
	if (m_frame > 7) {
		m_frame = 0;
	}
	m_hero->setStance(Hero::Stance(Hero::run1 + m_frame));
	//TODO make hero walk
	//TODO hero turns around based on direction
	/*TODO
	*		Move to JumpState on jump button pressed
	*		Move to AttackState on attack button pressed
	*		Move to HurtState on taking damage
	*		Maybe move to CrouchState on crouch press (possibly with slide?)
	*		Move to IdleState on release left/right buttons
	*/
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(HeroState::right_move_button)) {
		//TODO hero turns around based on direction
		if (m_hero->getPosition()->getGlobalTransform()[0][0] < 0.0f) {
			m_hero->getPosition()->applyTransform({  -1,0,0,0, 1,0,0,0,1 });
		}
	} else if (input->isKeyDown(HeroState::left_move_button)) {
		//TODO hero turns around based on direction
		if (m_hero->getPosition()->getGlobalTransform()[0][0] > 0.0f) {
			m_hero->getPosition()->applyTransform({ -1,0,0,0, 1,0,0,0,1 });
		}
	}
	else {
		m_shouldTransition = true;
		m_target = HeroStateMachine::idle_state;
	}
	m_hero->getPosition()->translate({ Hero::move_speed * deltaTime,0 });
}

void WalkState::draw(aie::Renderer2D * renderer)
{
}
