#include "stdafx.h"
#include "HeroState.h"
#include "HeroController.h"

const aie::EInputCodes HeroState::left_move_button = aie::EInputCodes::INPUT_KEY_A;
const aie::EInputCodes HeroState::right_move_button = aie::EInputCodes::INPUT_KEY_D;
const aie::EInputCodes HeroState::jump_button = aie::EInputCodes::INPUT_KEY_W;
const aie::EInputCodes HeroState::crouch_button = aie::EInputCodes::INPUT_KEY_S;
const aie::EInputCodes HeroState::attack_button = aie::EInputCodes::INPUT_KEY_SPACE;

HeroState::HeroState(HeroController* controller) : State(), m_controller(controller)
{
}

HeroState::~HeroState()
{
}

void HeroState::setHero(EntityPtr hero)
{
	m_hero = EntityWeakPtr(hero);
}

void HeroState::onEnter()
{
	State::onEnter();
}

void HeroState::onExit()
{
	State::onExit();
}
