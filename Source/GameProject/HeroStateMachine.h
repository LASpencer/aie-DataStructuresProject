#pragma once
#include "StateMachine.h"
#include "HeroState.h"

class Hero;

class HeroStateMachine :
	public StateMachine<HeroState>
{
public:
	HeroStateMachine(Hero* hero);
	~HeroStateMachine();

	enum states {
		idle_state,
		walk_state,
		crouch_state
	};

protected:
	Hero* m_hero;
};