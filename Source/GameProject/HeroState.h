#pragma once
#include "State.h"
#include "Input.h"

class Hero;

//TODO write and implement
//TODO write HeroStateMachine
class HeroState : public State {
public:
	HeroState(Hero* hero);
	virtual ~HeroState();

	virtual void onEnter();

	virtual void onExit();

	static const aie::EInputCodes left_move_button;
	static const aie::EInputCodes right_move_button;
	static const aie::EInputCodes jump_button;
	static const aie::EInputCodes crouch_button;
	static const aie::EInputCodes attack_button;

protected:
	Hero* m_hero;
};